#include "Player.h"
#include"../../../GameObject/Camera/CameraBase.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Terrains/TerrainBase.h"

#include"../../../GameObject/Object/ObjectBase.h"
#include"../../../GameObject/Object/Parts/Missile/Missile.h"
#include"../../../GameObject/Object/Body/CleanRobot/CleanRobot.h"
#include"../../../GameObject/Object/CardBoard/CardBoard.h"

#include"../../../main.h"

void Player::Init()
{
	CharacterBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Character/Player/Player2.gltf");
	m_adjustHeight = 1.7f;
	m_pos = { 0,m_adjustHeight ,0 };
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_dir = {};
	m_speed = 0.1f;
	m_color = { 1,1,1,1 };
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/UI/Reticle/Dot.png");
	m_spritePos = {};
	m_texSize = { 16,16 };
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

	//後で消す
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_pos.y += 0.5f; }

	//プレイヤーの各操作
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
}

void Player::PostUpdate()
{
	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);
	CollisionSphere();

	m_rotationMat = GetRotationMatrix();
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_rotationMat * m_transMat;
}

void Player::DrawSprite()
{
	m_rect = { 0,0,(long)m_texSize.x,(long)m_texSize.y };
	m_color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_spritePos.x, m_spritePos.y, 16, 16, &m_rect, &m_color);
}

void Player::Action()
{
	//当たり判定のリスト
	std::list<KdCollider::CollisionResult> rayRetList;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_keyFlg.Lbuuton == false && m_holdFlg == false)
		{
			//レイ情報用
			Math::Vector3 camPos;
			Math::Vector3 dir;
			float range = 0;
			//ここでどこからどの方向にレイを飛ばすのか情報を確立
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
					m_holdObj = obj;
					m_objType = obj->GetObjType();
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

			//当たっていたら
			if (hitFlg)
			{
				if (m_objType != eNone && m_objType != eContainer &&
					m_objType != eConver && m_objType != eProduceParts &&
					m_objType != eCardBoard)
				{
					m_holdObj->ChangeAttachFlg(false);
					m_holdObj->ChangeHoldFlg(true);

					m_holdFlg = true;
				}

				if (m_objType == eParts)
				{
					std::shared_ptr<KdGameObject> connectionObj = m_holdObj->GetRecieveObj().lock();
					if (connectionObj)
					{
						m_holdObj->RemoveConnectedPart(connectionObj);
						m_holdObj->RemoveConnectedPart(m_holdObj);
						connectionObj->RemoveConnectedPart(m_holdObj);
					}
				}
			}
			m_keyFlg.Lbuuton = true;
		}
	}
	else
	{
		m_keyFlg.Lbuuton = false;
	}

	//持ってるものを投げる
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (m_keyFlg.Rbutton == false && m_holdFlg == true)
		{
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (m_holdObj)
				{
					m_holdObj->ChangeHoldFlg(false);
					m_holdObj->ChangeThrowFlg(true);
				}
			}
			m_objType = eNone;
			m_holdFlg = false;
			m_holdObj = nullptr;
			m_keyFlg.Rbutton = true;
		}
	}
	else
	{
		m_keyFlg.Rbutton = false;
	}

	if (GetAsyncKeyState('F') & 0x8000)
	{
		if (m_keyFlg.F == false && m_holdFlg == true)
		{
			//レイ情報用
			Math::Vector3 camPos;
			Math::Vector3 dir;
			float range = 0;//ただの入れ物
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
							//m_pDebugWire->AddDebugSphere(nodePos, 0.5f, kRedColor);
						}
					}
				}
			}

			//最も近いノードが見つかった場合
			if (closestNode)
			{
				//各OBJのフラグやポインタの処理
				m_holdObj->ChangeHoldFlg(false);
				m_holdObj->ChangeAttachFlg(true);
				m_holdObj->ReciveOBJ(HitObj);
				m_holdObj->ReciveNode(closestNode);
				//接続してるならお互いにリストに追加する
				HitObj->AddConnectedPart(m_holdObj);
				m_holdObj->AddConnectedPart(HitObj);

				m_objType = eNone;
				m_holdFlg = false;
				closestNode = nullptr;
			}
			m_keyFlg.F = true;
		}

		//コンテナからパーツ取りだし
		if (m_keyFlg.F == false && m_holdFlg == false)
		{
			//レイ情報用
			Math::Vector3 camPos;
			Math::Vector3 dir;
			float range = 0;//ただの入れ物
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
			ray.m_type = KdCollider::TypeEvent;
			std::shared_ptr<KdGameObject> HitObj = std::make_shared<ObjectBase>();//当たったOBJの情報を保持
			//std::shared_ptr<Container> container = std::dynamic_pointer_cast<Container>(shared_from_this());

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->GetObjType() == KdGameObject::eContainer)
				{
					//これがレイとオブジェクトの当たり判定
					if (obj->Intersects(ray, &rayRetList))
					{
						HitObj = obj;
						//container = HitObj;
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

			int holdNumber = 0;
			ProductionType nowType = eNoneCont;
			if (hitFlg)
			{
				holdNumber = HitObj->PartsHoldNumber();
				nowType = HitObj->GetProdType();
			}

			if (holdNumber > 0)
			{
				std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(shared_from_this());
				switch (nowType)
				{
					case eMissile:
					{
						std::shared_ptr<ObjectBase> parts = std::make_shared<Missile>();
						parts->Init();
						parts->SetPos({ 0,2,0 });
						parts->SetPlayer(player);
						parts->ChangeHoldFlg(true);
						SceneManager::Instance().AddObject(parts);
						m_holdFlg = true;
						m_holdObj = parts;
						break;
					}
					case eCleanRobot:
					{
						std::shared_ptr<ObjectBase> body = std::make_shared<CleanRobot>();
						body->Init();
						body->SetPos({ 0,2,-2 });
						body->SetPlayer(player);
						body->ChangeHoldFlg(true);
						SceneManager::Instance().AddObject(body);
						m_holdFlg = true;
						m_holdObj = body;
						break;
					}
				}
			}
			m_keyFlg.F = true;
		}
	}
	else
	{
		m_keyFlg.F = false;
	}


	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_keyFlg.E == false && m_holdFlg == false)
		{
			//レイ情報用
			Math::Vector3 camPos;
			Math::Vector3 dir;
			float range = 0;//ただの入れ物
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
			ray.m_type = KdCollider::TypeEvent;
			std::shared_ptr<KdGameObject> HitObj = std::make_shared<ObjectBase>();//当たったOBJの情報を保持

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				//これがレイとオブジェクトの当たり判定
				if (obj->Intersects(ray, &rayRetList))
				{
					HitObj = obj;
				}
			}

			//レイが当たった場合数値の更新
			float overlap = 0;
			bool hitFlg = false;
			for (auto& ret : rayRetList)
			{
				if (overlap < ret.m_overlapDistance)
				{
					//データ更新
					overlap = ret.m_overlapDistance;
					hitFlg = true;
				}
			}

			//当たっているなら
			if (hitFlg)
			{
				//生産
				if (HitObj->GetObjType() == eProduceParts)
				{
					HitObj->ChangeProdFlg(true);
				}
			}

			m_objType = eNone;
			m_keyFlg.E = true;
		}

		if (m_keyFlg.E == false && m_holdFlg == true)
		{
			//レイ情報用
			Math::Vector3 camPos;
			Math::Vector3 dir;
			float range = 0;//ただの入れ物
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
			ray.m_type = KdCollider::TypeEvent;
			std::shared_ptr<KdGameObject> HitObj = std::make_shared<ObjectBase>();//当たったOBJの情報を保持

			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				//これがレイとオブジェクトの当たり判定
				if (obj->Intersects(ray, &rayRetList))
				{
					// obj が ObjectBase かどうかを確認してキャスト
					//std::shared_ptr<ObjectBase> baseObj = std::dynamic_pointer_cast<ObjectBase>(obj);
					//std::shared_ptr<CardBoard> baseObj = std::dynamic_pointer_cast<CardBoard>(obj);

					HitObj = obj;
					//HitObj = baseObj;
				}
			}

			//レイが当たった場合数値の更新
			float overlap = 0;
			bool hitFlg = false;
			for (auto& ret : rayRetList)
			{
				if (overlap < ret.m_overlapDistance)
				{
					//データ更新
					overlap = ret.m_overlapDistance;
					hitFlg = true;
				}
			}

			//当たっているなら
			if (hitFlg)
			{
				if (m_holdObj->GetConnectedPartsCount() == m_holdObj->GetTermsNum())
				{
					//すべての接続されたオブジェクトを保持
					std::set<std::shared_ptr<KdGameObject>> connectedParts;
					//すべての接続されたパーツを取得
					GetAllConnectedParts(m_holdObj, connectedParts);

					for (auto& part : connectedParts)
					{
						part->IsExpiredTrue();
					}
					HitObj->IncrementDeliverd();
				}
			}
			m_objType = eNone;
			m_holdFlg = false;
			m_holdObj = nullptr;
			m_keyFlg.E = true;
		}
	}
	else
	{
		m_keyFlg.E = false;
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (m_keyFlg.R == false && m_holdFlg == true)
		{
			m_holdObj->ChangeRotFlg(true);
			m_keyFlg.R = true;
		}
	}
	else
	{
		m_keyFlg.R = false;
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

void Player::CollisionSphere()
{
	////////////////////////////////////
	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;//スフィア
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3{ 0,-0.6,0 };
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround | KdCollider::TypeBump;
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
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
