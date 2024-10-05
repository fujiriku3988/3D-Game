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
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/UI/Reticle/Reticle.png");
	m_spritePos = {};
	m_texSize = { 64,64 };
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

void Player::DrawSprite()
{
	m_rect = { 0,0,(long)m_texSize.x,(long)m_texSize.y };
	m_color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_spritePos.x, m_spritePos.y,64,64,&m_rect,&m_color);
}

void Player::Action()
{
	//当たり判定のリスト
	std::list<KdCollider::CollisionResult> rayRetList;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (keyFlg.Lbuuton == false && m_holdFlg == false)
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

			//レイを飛ばす
			KdCollider::RayInfo ray;
			ray.m_pos = camPos;
			ray.m_dir = dir;
			ray.m_range = range;
			ray.m_type = KdCollider::TypeDamage;

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
			keyFlg.Lbuuton = true;
		}
	}
	else
	{
		keyFlg.Lbuuton = false;
	}

	if (GetAsyncKeyState('F') & 0x8000)
	{
		if (keyFlg.F == false)
		{
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
			std::shared_ptr<KdGameObject> HitObj = std::make_shared<ObjectBase>();//当たったOBJの情報を保持

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->GetObjType() == KdGameObject::eBody)
				{
					//これがレイとオブジェクトの当たり判定
					if (obj->Intersects(ray, &rayRetList))
					{
						HitObj = obj;
					}
				}
			}

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

			//当たり判定
			Math::Vector3 nodePos;//ノードの座標
			Math::Vector3 nodeDis;//ノードからの距離
			Math::Vector3 objDis;//オブジェクトとの距離
			const KdModelWork::Node* closestNode = nullptr; // 最も近いノードを保持するポインタ
			if (hitFlg)
			{
				for (auto& node : SceneManager::Instance().GetNodeList())
				{
					nodePos = (node->m_worldTransform * HitObj->GetMatrix()).Translation();
					nodeDis = hitPos - nodePos;//後で消す（ノードからの距離）
					objDis = hitPos - camPos;//後で消す（オブジェクトとの距離）
					if (objDis.Length() <= 2.0f)
					{
						if (nodeDis.Length() <= 1.0f)
						{
							closestNode = node;
							m_pDebugWire->AddDebugSphere(nodePos, 0.5f, kRedColor);
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
						obj->ReciveOBJ(HitObj);
						obj->ReciveNode(closestNode);
					}
				}
				m_objType = eNone;
				closestNode = nullptr;
			}
			keyFlg.F = true;
		}
	}
	else
	{
		keyFlg.F = false;
	}
	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("NODE:%d\n", SceneManager::Instance().GetNodeList().size());
	Application::Instance().m_log.AddLog("OBJ:%d\n", SceneManager::Instance().GetObjList().size());
	//Application::Instance().m_log.AddLog("lenNode:%f\n", nodeDis.Length());//うまい事距離は取れてそう
	//Application::Instance().m_log.AddLog("lenObj:%f\n", objDis.Length());//うまい事距離は取れてそう

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (keyFlg.Rbutton == false && m_holdFlg == true)
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
			keyFlg.Rbutton = true;
		}
	}
	else
	{
		keyFlg.Rbutton = false;
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
	m_degAng.x = std::clamp(m_degAng.x, -65.f, 65.f);
}
