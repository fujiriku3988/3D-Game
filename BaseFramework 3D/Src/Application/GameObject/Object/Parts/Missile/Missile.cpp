﻿#include "Missile.h"
#include"../../../Character/Player/Player.h"
#include"../../ObjectBase.h"
#include"../../../../main.h"

void Missile::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Structure/Missile/missile.gltf");
	m_pos = { 0,0,0 };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("missile", m_modelWork, KdCollider::TypeDamage);
	m_objType = eMissile;
}

void Missile::Update()
{
	m_pos += m_dir * m_speed;
	//m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	if (m_holdFlg)
	{
		m_gravity = 0;
		if (m_wpPlayer.expired() == false)
		{
			std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
			m_pos = spPlayer->GetPos();
			m_dir = spPlayer->GetMatrix().Backward();
			m_dir.Normalize();
		}
	}

	//仮でクリーンロボに付ける（修正が必要）
	if (m_attachFlg)
	{
		/*if (m_wpCharaBody.expired() == false)
		{
			std::shared_ptr<ObjectBase>spRobo = m_wpCharaBody.lock();
			m_pos = spRobo->GetNodeMatrix().Translation();
		}*/
		//m_pos = { 0,5,0 };
		if (m_reciveNode)
		{
			if (m_wpReciveObj.expired() == false)
			{
				std::shared_ptr<KdGameObject>spObj = m_wpReciveObj.lock();
				m_pos = (m_reciveNode->m_worldTransform * spObj->GetMatrix()).Translation();
				//m_transMat = (m_reciveNode->m_worldTransform * spObj->GetMatrix());
			}
		}
	}

	if (m_throwFlg)
	{
		//m_dir = 
		m_speed = 1.0f;
		m_throwFlg = false;
	}

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;
}

void Missile::PostUpdate()
{

}