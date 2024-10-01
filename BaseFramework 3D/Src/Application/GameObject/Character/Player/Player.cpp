#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Terrains/TerrainBase.h"
#include"../../../GameObject/Object/ObjectBase.h"
#include"../../../main.h"

void Player::Init()
{
	CharacterBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Tank/Tank.gltf");
	m_adjustHeight = 1.7f;
	m_pos = { 0,m_adjustHeight ,0 };
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_dir = {};
	m_speed = 0.1f;
	m_color = { 1,1,1,1 };
	m_keyFlg = false;
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

	m_rotationMat = GetRotationMatrix();
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_rotationMat * m_transMat;

	//Application::Instance().m_log.AddLog("LengthXXXXXX%f\n", m_pos.x);
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
		//ここでどこからどの方向に例を飛ばすのか情報を確立
		if (m_wpCamera.expired() == false)
		{
			camPos = m_wpCamera.lock()->GetPos();
			m_wpCamera.lock()->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, dir, range);
		}
		Math::Vector3 structLeng = camPos;

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
				obj->ChangeAttachFlg(false);
				obj->ChangeHoldFlg(true);
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

	Application::Instance().m_log.Clear();

	Math::Vector3 aho;//後で消す
	//Math::Matrix aho;//後で消す
	Math::Vector3 aho2;//後で消す
	Math::Vector3 aho3;//後で消す
	std::shared_ptr<KdGameObject> m = std::make_shared<ObjectBase>();
	std::shared_ptr<KdGameObject> o = std::make_shared<ObjectBase>();
	const KdModelWork::Node* closestNode = nullptr; // 最も近いノードを保持するポインタ
	if (GetAsyncKeyState('F') & 0x8000)
	{
		//if (m_keyFlg)return;

		Math::Vector3 camPos;
		Math::Vector3 dir;
		float range = 0;//ただの入れ物
		if (m_wpCamera.expired() == false)
		{
			//m_wpCamera.lock()->WorkCamera()->ConvertWorldToScreenDetail();
			camPos = m_wpCamera.lock()->GetPos();
			m_wpCamera.lock()->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, dir, range);
		}

		//レイを飛ばす
		KdCollider::RayInfo ray;
		ray.m_pos = camPos;
		ray.m_dir = dir;
		ray.m_range = range;
		ray.m_type = KdCollider::TypeDamage;


		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetObjType() == KdGameObject::eCleanRobot)
			{
				//これがレイとオブジェクトの当たり判定
				if (obj->Intersects(ray, &rayRetList))
				{
					//aho = obj->GetNodeMatrix().Translation();
					//obj->AddNode();
					o = obj;
				}
			}
		}

		//一番近くの位置を探す
		float overlap = 0;
		Math::Vector3 hitPos;
		bool hitFlg = false;
		for (auto& ret : rayRetList)
		{
			if (overlap < ret.m_overlapDistance)
			{
				//データ更新
				overlap = ret.m_overlapDistance;
				//当たった座標を保存
				hitPos = ret.m_hitPos;
				hitFlg = true;
			}
		}

		if (hitFlg)
		{
			for (auto& node : SceneManager::Instance().GetNodeList())
			{
				aho = (node->m_worldTransform * o->GetMatrix()).Translation();
				//aho = node->m_worldTransform.Translation();
				//aho = node->m_localTransform.Translation();
				//aho = node->m_localTransform.Translation();
				aho2 = hitPos - aho;//後で消す（ノードからの距離）
				aho3 = hitPos - camPos;//後で消す（オブジェクトとの距離）
				if (aho3.Length() <= 2.0f)
				{
					if (aho2.Length() <= 1.0f)
					{
						closestNode = node;
						m_pDebugWire->AddDebugSphere(aho, 0.5f, kRedColor);
					}
				}
			}
		}

		
		//最も近いノードが見つかった場合
		if (closestNode)
		{
			//持ってるオブジェクトの処理
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->GetObjType() == m_objType)
				{
					obj->ChangeHoldFlg(false);
					obj->ChangeAttachFlg(true);
					obj->ReciveOBJ(o);
					obj->ReciveNode(closestNode);
				}	
			}
			m_objType = eNone;
			closestNode = nullptr;
		}

		m_keyFlg = true;
	}
	else
	{
		m_keyFlg = false;
	}

	Application::Instance().m_log.AddLog("X:%f\n", aho.x);//うまい事距離は取れてそう
	Application::Instance().m_log.AddLog("Y:%f\n", aho.y);//うまい事距離は取れてそう
	Application::Instance().m_log.AddLog("Z:%f\n", aho.z);//うまい事距離は取れてそう

	Application::Instance().m_log.AddLog("LengthNode%f\n", aho2.Length());//うまい事距離は取れてそう
	Application::Instance().m_log.AddLog("LengthRobo%f\n", aho3.Length());//うまい事距離は取れてそう
	Application::Instance().m_log.AddLog("NODE:%d\n", SceneManager::Instance().GetNodeList().size());//うまい事距離は取れてそう
	Application::Instance().m_log.AddLog("OBJ:%d\n", SceneManager::Instance().GetObjList().size());//うまい事距離は取れてそう
	//Application::Instance().m_log.AddLog("LengthXXXXXX%f\n", m_pos.x);

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->GetObjType() == m_objType)
			{
				obj->ChangeHoldFlg(false);
				obj->ChangeThrowFlg(true);
			}
		}
		m_objType = eNone;
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
