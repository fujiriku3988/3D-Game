#include "CleanRobot.h"
#include"../Player/Player.h"

void CleanRobot::Init()
{
	CharacterBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/CleanRobot/cleanRobot.gltf");
	m_pos = {};
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("robot", m_modelWork, KdCollider::TypeDamage);
	m_objType = eCleanRobot;
}

void CleanRobot::Update()
{
	Math::Matrix playerMat;
	

	transMat = Math::Matrix::CreateTranslation(m_pos);

	if (m_holdFlg)
	{
		if (m_wpPlayer.expired() == false)
		{
			std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
			playerMat = Math::Matrix::CreateTranslation(spPlayer->GetPos());
			m_pos = spPlayer->GetPos();
		}
		//m_mWorld = transMat * playerMat;
		m_mWorld = transMat;
	}
	else
	{
		m_mWorld = transMat;
	}

}
