﻿#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"
#include"../../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../../Scene/SceneManager.h"
#include"../../../../Framework/Effekseer/KdEffekseerManager.h"

#include"../../../GameObject/UI/GameTime/GameTime.h"

#include"../../../GameObject/Effect/smoke/smoke.h"

#include"../../../main.h"
#include <algorithm>

void Player::Init(const std::string _filePath)
{
	CharacterBase::Init();

	//モデルが読み込まれてないなら
	if (m_modelWork == nullptr)
	{
		m_modelWork = std::make_shared<KdModelWork>();
		m_modelWork->SetModelData("Asset/Models/Character/wizard/Player.gltf");
	}

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "Player", "pos");
	m_dir = JsonManager::Instance().GetParamVec3(_filePath, "Player", "dir");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "Player", "scale");
	m_adjHeightRay = JsonManager::Instance().GetParamVec3(_filePath, "Player", "adjustHeightRay");
	m_adjHeightSph = JsonManager::Instance().GetParamVec3(_filePath, "Player", "adjustHeightSph");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Player", "color");
	m_stepHeight = JsonManager::Instance().GetParam<float>(_filePath, "Player", "stepHeight");
	m_jumpPow = JsonManager::Instance().GetParam<float>(_filePath, "Player", "jumpPow");
	m_jumpVelocity = JsonManager::Instance().GetParam<float>(_filePath, "Player", "jumpVelocity");
	m_gravity = JsonManager::Instance().GetParam<float>(_filePath, "Player", "gravity");
	m_gravityPow = JsonManager::Instance().GetParam<float>(_filePath, "Player", "gravityPow");
	m_speed = JsonManager::Instance().GetParam<float>(_filePath, "Player", "speed");
	m_sphereRad = JsonManager::Instance().GetParam<float>(_filePath, "Player", "sphereRadius");
	m_effDelay = JsonManager::Instance().GetParam<int>(_filePath, "Player", "effDelay");
	m_effMgcCircleSpeed = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effMgcSpeed");
	m_effMgcCircleSize = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effMgcSize");
	m_effTeleportSpeed = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effTeleSpeed");
	m_effTeleportSize = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effTeleSize");
	m_efkSeerScaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Player", "efkScaleMAX");
	m_gameTimeFlg = false;

	m_tex = std::make_shared<KdTexture>();

	m_filePath = _filePath;
}

void Player::Update()
{
	if (m_wpCamera.expired() == false)
	{
		m_spCamera = m_wpCamera.lock();
	}

	//移動
	m_dir = Math::Vector3::Zero;
	m_ctrlFlg.move = false;
	if (m_ctrlFlg.stop == false)
	{
		//プレイヤーの移動操作
		MovementControll();

		//プレイヤーの特殊操作
		Action();
	}

	Rotation();

	//ジャンプ力の計算
	if (m_ctrlFlg.jump == true)
	{
		m_pos.y += m_jumpVelocity;
	}
	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;

	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("%f", m_pos.y);
}

void Player::PostUpdate()
{
	//当たり判定（レイ）
	CollisionDetection();
	//当たり判定（スフィア）
	CollisionSphere();

	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_rotationMat = GetRotationYMatrix();
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_scaleMat * m_rotationMat * m_transMat;
}

void Player::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void Player::Action()
{
	//定数
	constexpr int DelayConstant = 20;
	constexpr float efkSeerScaleInc = 0.05f;

	//カメラ情報取得
	m_spCamera = m_wpCamera.lock();
	if (!m_spCamera)
	{
		return;
	}

	//魔法陣を出す処理
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_ctrlFlg.E == false)
		{
			//魔法陣がないなら
			if (m_ctrlFlg.mgcCircle == false)
			{
				//魔法陣の位置を記憶
				SetMagicCircle();
				//再生
				//魔法陣のハンドル保持
				m_wpEffekseer = KdEffekseerManager::GetInstance().Play("MagicCircle.efkefc", m_pos + Math::Vector3::Up,
					m_effMgcCircleSize, m_effMgcCircleSpeed, false);

				//SE音出す
				KdAudioManager::Instance().Play("Asset/Sounds/SE/magicCircle.wav", false, KdAudioManager::Instance().GetSEVolume());
				m_ctrlFlg.mgcCircle = true;
			}
			else
			{
				//魔法陣に移動
				TeleportToMagicCircle();
				//SE音出す
				KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, KdAudioManager::Instance().GetSEVolume());

				std::shared_ptr<KdEffekseerObject> spEff = m_wpEffekseer.lock();
				if (spEff)
				{
					//エフェクトを止める
					spEff->StopEffect();
					m_effMgcCircleSize = JsonManager::Instance().GetParam<float>(m_filePath, "Player", "effMgcSize");
				}

				KdEffekseerManager::GetInstance().Play("GoalPoint.efkefc", m_pos,
					m_effTeleportSize, m_effTeleportSpeed, false);

				m_ctrlFlg.mgcCircle = false;
			}
		}
		m_ctrlFlg.E = true;
	}
	else
	{
		m_ctrlFlg.E = false;
	}

	//魔法陣を大きくする処理
	std::shared_ptr<KdEffekseerObject> spEff = m_wpEffekseer.lock();
	if (spEff)
	{
		//スケールを徐々に大きくする処理
		//最大スケールを制限
		if (m_effMgcCircleSize < m_efkSeerScaleMAX)
		{
			//スケールの増加速度
			m_effMgcCircleSize += efkSeerScaleInc;
			spEff->SetScale(m_effMgcCircleSize);
		}
	}

	//動いたときにでる足煙
	//ジャンプ中か？
	if (m_ctrlFlg.jump == false)
	{
		if (m_ctrlFlg.move == true)
		{
			m_effDelay--;
			if (m_effDelay < NumberConstants::NumZero)
			{
				std::shared_ptr<smoke> smokeEff = std::make_shared<smoke>();
				smokeEff->Init("Asset/Data/Json/Effect/Smoke/Smoke.json");
				smokeEff->SetPos(m_pos + Math::Vector3::TransformNormal(Math::Vector3::Forward, m_rotationMat));
				smokeEff->SetCamera(m_spCamera);
				SceneManager::Instance().AddObject(smokeEff);
				m_effDelay = DelayConstant;
			}
		}
	}
}

void Player::MovementControll()
{
	//ジャンプ
	if (m_ctrlFlg.stop == false)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (m_ctrlFlg.space == false)
			{
				m_jumpVelocity = m_jumpPow;
				m_ctrlFlg.jump = true;
			}
			m_ctrlFlg.space = true;
		}
		else
		{
			m_ctrlFlg.space = false;
		}
	}

	//移動
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_dir += Math::Vector3::TransformNormal(Math::Vector3::Backward, m_spCamera->GetRotationYMatrix());
		m_ctrlFlg.move = true;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_dir += Math::Vector3::TransformNormal(Math::Vector3::Forward, m_spCamera->GetRotationYMatrix());
		m_ctrlFlg.move = true;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_dir += Math::Vector3::TransformNormal(Math::Vector3::Left, m_spCamera->GetRotationYMatrix());
		m_ctrlFlg.move = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_dir += Math::Vector3::TransformNormal(Math::Vector3::Right, m_spCamera->GetRotationYMatrix());
		m_ctrlFlg.move = true;
	}


	//動いたらゲームタイムを動かす
	if (m_ctrlFlg.move)
	{
		std::shared_ptr<GameTime> spGameTime = m_wpGameTime.lock();
		//nullチェック
		if (spGameTime)
		{
			if (m_gameTimeFlg == false)
			{
				spGameTime->StartTime();
				m_gameTimeFlg = true;
			}
		}
	}
}

void Player::Rotation()
{
	//定数
	constexpr float AngleMAX = 5.0f;
	constexpr float AngChangeAmount = 0.75f;
	constexpr float DegAngMAX = 360.0f;

	if (m_ctrlFlg.move == true)
	{
		//移動中（移動キーが押された）
		//正規化
		m_dir.Normalize();//長さを１にする

		//今キャラが向いている方向
		//①キャラの回転行列を作成
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAng.y));
		//②現在の方向（ベクトル）を求める
		Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3::Backward, nowRotMat);

		//向きたい方向
		Math::Vector3 toVec = m_dir;

		//角度を求める
		//内積…ベクトルA＊ベクトルB＊コサインなす角
		//			１			１		θ
		float d = nowVec.Dot(toVec);

		//丸め誤差の都合上「１」を超える可能性があるのでクランプ（遮断）する
		//decltype(d)で型をdに合わせる
		d = std::clamp(d, static_cast<decltype(d)>(-NumberConstants::NumOne),
			static_cast<decltype(d)>(NumberConstants::NumOne));//(補正する値、最小値、最大値)

		//角度を求める
		float ang = DirectX::XMConvertToDegrees(acos(d));

		//少しずつ回転するようにする
		if (ang >= AngChangeAmount)
		{
			if (ang > AngleMAX)
			{
				ang = AngleMAX;
			}

			//どっちに回転するかを求める
			//外積…２つのベクトルに対して垂直に伸びるベクトル
			Math::Vector3 c = toVec.Cross(nowVec);
			c.Normalize();

			//
			if (c.y > NumberConstants::NumZero)
			{
				m_degAng.y -= ang;
			}
			else
			{
				m_degAng.y += ang;
			}

			//１回転は３６０度
			if (m_degAng.y >= DegAngMAX) { m_degAng.y -= DegAngMAX; }
			if (m_degAng.y <= -DegAngMAX) { m_degAng.y += DegAngMAX; }
		}

		m_dir.Normalize();
	}
}

void Player::CollisionDetection()
{
	//レイ判定
	KdCollider::RayInfo ray;
	//飛ばす位置
	ray.m_pos = m_pos + m_adjHeightRay;
	//長さ
	static const float enableStepHeight = m_stepHeight;
	ray.m_range = enableStepHeight;
	//方向
	ray.m_dir = Math::Vector3::Down;
	//タイプ
	ray.m_type = KdCollider::TypeGround | KdCollider::TypeEvent;
	//当たったOBJの情報を格納するリスト
	std::list<KdCollider::CollisionResult>retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(ray, &retRayList))
		{
			if (obj->GetObjType() == ePressurePlate || obj->GetObjType() == eGoalPoint)
			{
				if (m_ctrlFlg.collision == false)
				{
					obj->HitFlg(true);
				}
				m_ctrlFlg.collision = true;
			}
			else
			{
				m_ctrlFlg.collision = false;
			}
		}
	}

	bool hit = false;
	float maxOverLap = {};
	Math::Vector3 hitPos = {};

	//リストにあるものと判定
	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}
	//あたっているなら
	if (hit)
	{
		m_pos = hitPos;
		m_gravity = {};
		m_ctrlFlg.jump = false;
		m_jumpVelocity = {};
	}
}

void Player::Restart()
{
	std::shared_ptr<KdEffekseerObject> spEff = m_wpEffekseer.lock();
	if (spEff)
	{
		//エフェクトを止める
		spEff->StopEffect();
		m_effMgcCircleSize = JsonManager::Instance().GetParam<float>(m_filePath, "Player", "effMgcSize");
	}

	Init(m_filePath);
	m_ctrlFlg.mgcCircle = false;
	m_ctrlFlg.stop = false;
}

void Player::CollisionSphere()
{
	////////////////////////////////////
	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;//スフィア
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + m_adjHeightSph;
	//球の半径を設定
	sphere.m_sphere.Radius = m_sphereRad;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround | KdCollider::TypeBump;
	//球が当たったオブジェクトの情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
		}
	}
	//球リストから一番近いオブジェクトを検出
	float maxOverLap = NumberConstants::NumZero;
	Math::Vector3 hitDir = {};
	bool ishit = false;
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;//当たった方向
			ishit = true;
		}

	}

	if (ishit)
	{
		//方向ベクトルは長さ１にする必要がある 
		hitDir.Normalize();
		//押し戻し
		m_pos += hitDir * maxOverLap;
	}
}

void Player::SetMagicCircle()
{
	// プレイヤーの現在位置を魔法陣の位置として記録
	m_magicCirclePos = GetPos();
	m_ctrlFlg.mgcCircle = true;
}

void Player::TeleportToMagicCircle()
{
	if (m_ctrlFlg.mgcCircle == true)
	{
		SetPos(m_magicCirclePos);
		m_ctrlFlg.mgcCircle = false;
	}
}
