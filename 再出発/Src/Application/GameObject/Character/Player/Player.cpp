#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"

#include"../../../Scene/SceneManager.h"
#include"../../../../Framework/Effekseer/KdEffekseerManager.h"

#include"../../../GameObject/Terrains/TerrainBase.h"

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
	m_adjustHeight = JsonManager::Instance().GetParamVec3(_filePath, "Player", "adjustHeight");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Player", "color");
	m_stepHeight = JsonManager::Instance().GetParam<float>(_filePath, "Player", "stepHeight");
	m_jumpPow = JsonManager::Instance().GetParam<float>(_filePath, "Player", "jumpPow");
	m_jumpVelocity = JsonManager::Instance().GetParam<float>(_filePath, "Player", "jumpVelocity");
	m_gravity = JsonManager::Instance().GetParam<float>(_filePath, "Player", "gravity");
	m_gravityPow = JsonManager::Instance().GetParam<float>(_filePath, "Player", "gravityPow");
	m_speed = JsonManager::Instance().GetParam<float>(_filePath, "Player", "speed");
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
	Math::Vector3 m_dir = Math::Vector3::Zero;

	bool moveFlg = false;
	if (m_ctrlFlg.stop == false)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_dir += Math::Vector3::TransformNormal(Math::Vector3::Backward, m_spCamera->GetRotationYMatrix());
			moveFlg = true;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_dir += Math::Vector3::TransformNormal(Math::Vector3::Forward, m_spCamera->GetRotationYMatrix());
			moveFlg = true;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_dir += Math::Vector3::TransformNormal(Math::Vector3::Left, m_spCamera->GetRotationYMatrix());
			moveFlg = true;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_dir += Math::Vector3::TransformNormal(Math::Vector3::Right, m_spCamera->GetRotationYMatrix());
			moveFlg = true;
		}
		//プレイヤーの各操作
		Action();
	}
	if (moveFlg == true)
	{
		//移動中（移動キーが押された）
		//正規化
		m_dir.Normalize();//長さを１にする

		//今キャラが向いている方向
		//①キャラの回転行列を作成
		Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAng.y));
		//②現在の方向（ベクトル）を求める
		Math::Vector3 nowVec = Math::Vector3::TransformNormal({ 0,0,1 }, nowRotMat);

		//向きたい方向
		Math::Vector3 toVec = m_dir;

		//角度を求める
		//内積…ベクトルA＊ベクトルB＊コサインなす角
		//			１			１		θ
		//結果、求まる値はコサインθになる
		float d = nowVec.Dot(toVec);

		//丸め誤差の都合上「１」を超える可能性があるのでクランプ（遮断）する
		//丸め誤差…小数点以下を省略した際に生じる誤差
		d = std::clamp(d, -1.0f, 1.0f);//(補正する値、最小値、最大値)

		//角度を求める
		float ang = DirectX::XMConvertToDegrees(acos(d));

		//少しずつ回転するようにする
		if (ang >= 0.1f)
		{
			if (ang > 5)
			{
				ang = 5.0f;
			}

			//どっちに回転するかを求める
			//外積…２つのベクトルに対して垂直に伸びるベクトル
			Math::Vector3 c = toVec.Cross(nowVec);
			c.Normalize();

			//
			if (c.y > 0)
			{
				m_degAng.y -= ang;
			}
			else
			{
				m_degAng.y += ang;
			}

			//１回転は３６０度だよ
			if (m_degAng.y >= 360) { m_degAng.y -= 360.0f; }
			if (m_degAng.y <= -360) { m_degAng.y += 360.0f; }
		}

		m_dir.Normalize();
	}


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
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_ctrlFlg.E == false)
		{
			std::shared_ptr<KdEffekseerObject> spEffect = m_wpEffect.lock();
			if (spEffect)
			{
				//エフェクトを止める
				spEffect->StopEffect();
			}
			//魔法陣の位置を記憶
			SetMagicCircle();
			//再生
			m_wpEffect = KdEffekseerManager::GetInstance().Play("mahoujin.efkefc", m_pos + Math::Vector3{ 0,1,0 }, 1, 1, true);
		}
		m_ctrlFlg.E = true;
	}
	else
	{
		m_ctrlFlg.E = false;
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_ctrlFlg.Q == false)
		{
			//魔法陣に移動
			TeleportToMagicCircle();
			std::shared_ptr<KdEffekseerObject> spEffect = m_wpEffect.lock();
			if (spEffect)
			{
				//エフェクトを止める
				spEffect->StopEffect();
			}
		}
		m_ctrlFlg.Q = true;

	}
	else
	{
		m_ctrlFlg.Q = false;
	}
}

void Player::CollisionDetection()
{
	//レイ判定
	KdCollider::RayInfo ray;
	//飛ばす位置
	ray.m_pos = m_pos + m_adjustHeight;
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
	sphere.m_sphere.Center = m_pos + Math::Vector3{ 0,0.8,0 };
	//球の半径を設定
	sphere.m_sphere.Radius = 0.7f;
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
	float maxOverLap = 0;
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
	//ShowMagicCircleEffect();
}

void Player::TeleportToMagicCircle()
{
	if (m_ctrlFlg.mgcCircle == true)
	{
		SetPos(m_magicCirclePos);
		m_ctrlFlg.mgcCircle = false;
	}
	//ShowTeleportEffect();
}
