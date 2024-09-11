#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Terrains/TerrainBase.h"

void Player::Init()
{
	CharacterBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Tank/Tank.gltf");
	m_adjustHeight = 2.0f;
	m_pos = {0,m_adjustHeight ,0};
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_dir = {};
	m_speed = 0.1f;
	m_color = { 1,1,1,1 };
}

void Player::Update()
{
	if (m_wpCamera.expired() == false)
	{
		m_spCamera = m_wpCamera.lock();
	}

	//後で消す
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_pos.y += 1.0f; }
	
	Action();

	//移動
	Math::Vector3 m_dir = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000) { m_dir.z += 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_dir.z -= 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_dir.x -= 1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_dir.x += 1.0f; }
	m_dir = m_dir.TransformNormal(m_dir, GetRotationYMatrix());
	m_dir.Normalize();
	//回転
	UpdateRotateByMouse();

	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	rotationMat = GetRotationMatrix();
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotationMat * transMat;
}

void Player::Action()
{
	//当たり判定のリスト
	std::list<KdCollider::CollisionResult> rayRetList;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		Math::Vector3 camPos;
		Math::Vector3 dir;
		float range = 0;//ただの入れ物
		if (m_wpCamera.expired() == false)
		{
			camPos = m_wpCamera.lock()->GetPos();
			m_wpCamera.lock()->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, dir, range);
		}
		//ここまででどこからどの方向に例を飛ばすのか情報を確立

		//レイを飛ばす
		KdCollider::RayInfo ray;
		ray.m_pos = camPos;
		ray.m_dir = dir;
		ray.m_range = range;
		ray.m_type = KdCollider::TypeDamage;

		//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range, kGreenColor);

		
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			//これがレイとオブジェクトの当たり判定
			if (obj->Intersects(ray, &rayRetList))
			{
				obj->HoldFlgOn();
				m_objType = obj->GetObjType();
			}
		}

		//一番近くの位置を探す
		float overlap = 0;
		Math::Vector3 hitPos;
		for (auto& ret : rayRetList)
		{
			if (overlap < ret.m_overlapDistance)
			{
				//データ更新
				overlap = ret.m_overlapDistance;
				//当たった座標を保存
				hitPos = ret.m_hitPos;
			}
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetObjType() == m_objType)
			{
				obj->HoldFlgOff();
			}
		}
	}
}

void Player::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_degAng.x = std::clamp(m_degAng.x, -45.f, 45.f);
}
