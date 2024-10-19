#include "Missile.h"
#include"../../ObjectBase.h"

#include"../../../Character/Player/Player.h"
#include"../../../Object/ProduceParts/ProduceParts.h"
#include"../../../Object/Container/Container.h"

#include"../../../../main.h"
#include"../../../../Scene/SceneManager.h"

void Missile::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Parts/Missile/missile.gltf");
	m_pos = { 0,0,0 };
	m_adjustHeight = 0.5f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("missile", m_modelWork, KdCollider::TypeDamage);
	m_objType = eParts;
}

void Missile::Update()
{
	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);
	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeDamage, m_adjustHeight);

	Math::Matrix playerRotMat;
	//手に持つ処理
	if (m_holdFlg)
	{
		m_gravity = 0;
		if (m_wpPlayer.expired() == false)
		{
			m_spPlayer = m_wpPlayer.lock();
			for (auto& node : SceneManager::Instance().GetNodeList())
			{
				if (node->m_name == "hold")
				{
					m_pos = (node->m_worldTransform * m_spPlayer->GetMatrix()).Translation();
					m_rotationMat = m_spPlayer->GetRotationMatrix();
				}
			}
			m_dir = m_spPlayer->GetMatrix().Backward();
			m_dir.Normalize();
		}
	}

	//Bodyに着ける
	if (m_attachFlg)
	{
		if (m_reciveNode)
		{
			if (m_wpReciveObj.expired() == false)
			{
				std::shared_ptr<KdGameObject>spObj = m_wpReciveObj.lock();
				m_pos = (m_reciveNode->m_worldTransform * spObj->GetMatrix()).Translation();
			}
		}
	}

	//投げる処理
	if (m_throwFlg)
	{
		m_speed = 1.0f;
		m_throwFlg = false;
	}

	//生産された時の処理
	if (m_prodFlg)
	{
		//生成時の移動処理
		m_dir = GetMatrix().Up();
		m_dir.Normalize();
		m_speed = 0.02f;

		//コンテナの座標
		Math::Vector3 containerPos;
		//コンテナの距離
		Math::Vector3 containerDis;
		//ポインタロック
		m_spContainer = m_wpContainer.lock();
		if (m_spContainer)
		{
			containerPos = m_spContainer->GetPos();
			containerDis = containerPos - m_pos;
			if (containerDis.Length() < 2.f)
			{
				m_spContainer->IncrementParts();
				m_spContainer->SetContainerType(eMissile);
				m_isExpired = true;
			}
		}
	}

	//UpdateRotateByMouse();

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_rotMatZ = Math::Matrix::CreateRotationZ(m_rot.z);
	//m_mWorld = m_scaleMat * m_rotMatZ * playerRotMat * m_transMat;
	m_mWorld = m_scaleMat * m_rotMatZ * m_rotationMat * m_transMat;

	//Application::Instance().m_log.Clear();
	//Application::Instance().m_log.AddLog("ConnectMissile:%d\n", m_connectedParts.size());
}

void Missile::PostUpdate()
{

}

void Missile::UpdateRotateByMouse()
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
