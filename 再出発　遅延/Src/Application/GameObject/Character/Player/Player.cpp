#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"
#include"../../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../../Scene/SceneManager.h"
#include"../../../../Framework/Effekseer/KdEffekseerManager.h"

#include"../../../GameObject/Terrains/TerrainBase.h"
#include"../../../GameObject/Effect/smoke/smoke.h"
#include"../../../GameObject/Object/ObjectBase.h"

#include"../../../main.h"

void Player::Init(const std::string _filePath)
{
	CharacterBase::Init();

	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Character/wizard/Player.gltf");

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
	m_effSize = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effSize");
	m_effSpeed = JsonManager::Instance().GetParam<float>(_filePath, "Player", "effSpeed");

	m_tex = std::make_shared<KdTexture>();

	m_filePath = _filePath;
}

void Player::Update()
{
	//ノード追加
	{
		AddNode();
	}

	if (m_wpCamera.expired() == false)
	{
		m_spCamera = m_wpCamera.lock();
	}

	//ジャンプ
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

	if (m_ctrlFlg.jump == true)
	{
		m_pos.y += m_jumpVelocity;
	}

	//移動
	m_dir = Math::Vector3::Zero;

	m_ctrlFlg.move = false;
	if (m_ctrlFlg.stop == false)
	{
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
		//プレイヤーの各操作
		Action();
	}

	Rotation();

	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
}

void Player::PostUpdate()
{
	CollisionDetection();
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

	m_spCamera = m_wpCamera.lock();
	if (!m_spCamera)
	{
		return;
	}


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
				m_wpEffekseer = KdEffekseerManager::GetInstance().Play("MagicCircle.efkefc", m_pos + Math::Vector3::Up,
																		m_effSize, m_effSpeed, false);
				m_ctrlFlg.mgcCircle = true;
			}
			else
			{
				//魔法陣に移動
				TeleportToMagicCircle();
				std::shared_ptr<KdEffekseerObject> spEff = m_wpEffekseer.lock();
				if (spEff)
				{
					//エフェクトを止める
					spEff->StopEffect();
				}
				m_ctrlFlg.mgcCircle = false;
			}
		}
		m_ctrlFlg.E = true;
	}
	else
	{
		m_ctrlFlg.E = false;
	}

	if (m_ctrlFlg.jump == false)
	{
		if (m_ctrlFlg.move == true)
		{
			m_effDelay--;
			if (m_effDelay < NumberConstants::NumZero)
			{
				std::shared_ptr<smoke> smokeEff = std::make_shared<smoke>();
				smokeEff->Init("Asset/Data/Json/Effect/Smoke/Smoke.json");
				smokeEff->SetPos(m_pos);
				smokeEff->SetCamera(m_spCamera);
				SceneManager::Instance().AddObject(smokeEff);
				m_effDelay = DelayConstant;
			}
		}
	}
}

void Player::Rotation()
{
	//定数
	constexpr float AngleMAX = 5.0f;
	constexpr float AngChangeAmount = 0.1f;
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
		//結果、求まる値はコサインθになる
		float d = nowVec.Dot(toVec);

		//丸め誤差の都合上「１」を超える可能性があるのでクランプ（遮断）する
		//丸め誤差…小数点以下を省略した際に生じる誤差
		d = std::clamp(d, -NumberConstants::NumOne, NumberConstants::NumOne);//(補正する値、最小値、最大値)

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

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit)
	{
		m_pos = hitPos;
		m_gravity = {};
		m_ctrlFlg.jump = false;
		m_jumpVelocity = {};
	}
}

void Player::AddNode()
{
	if (m_modelWork)
	{
		if (m_addNodeFlg)
		{
			//ノード追加
			m_pNode = m_modelWork->FindNode("hold");
			if (m_pNode) { SceneManager::Instance().AddNode(m_pNode); }
			m_addNodeFlg = false;
		}
	}
}

void Player::Restart()
{
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
