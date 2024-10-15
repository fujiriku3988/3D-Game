#include "Missile.h"
#include"../../ObjectBase.h"

#include"../../../Character/Player/Player.h"
#include"../../../Object/ProduceParts/ProduceParts.h"
#include"../../../Object/Container/Container.h"

#include"../../../../main.h"

void Missile::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Parts/Missile/missile.gltf");
	m_pos = { 0,0,0 };
	m_adjustHeight = -0.0f;
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
	//m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);
	Math::Matrix playerMat;
	//手に持つ処理
	if (m_holdFlg)
	{
		Math::Vector3 adjust = { 0,0,1 };
		//Math::Matrix adjust = Math::Matrix::CreateTranslation({ 0,0,2 });
		m_gravity = 0;
		if (m_wpPlayer.expired() == false)
		{
			//プレイヤーの前にノード持たせればいいなじゃね？
			m_spPlayer = m_wpPlayer.lock();
			m_pos = m_spPlayer->GetPos() + adjust;
			//playerMat = m_spPlayer->GetMatrix();//* adjust;
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

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_rotMatZ = Math::Matrix::CreateRotationZ(m_rot.z);
	m_mWorld = m_scaleMat * m_rotMatZ * m_transMat;
}

void Missile::PostUpdate()
{

}
