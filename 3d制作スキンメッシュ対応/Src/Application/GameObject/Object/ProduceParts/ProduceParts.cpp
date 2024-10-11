#include "ProduceParts.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Object/Parts/Missile/Missile.h"
#include"../../../GameObject/Object/Body/CleanRobot/CleanRobot.h"

void ProduceParts::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Structure/PartsBox/PartsBox.gltf");
	m_pos = { -5,0,5 };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PartsBox", m_modelWork, KdCollider::TypeEvent);
	m_objType = eProduceParts;
}

void ProduceParts::Update()
{
	m_pos += m_dir * m_speed;
	//m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	Action();

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;
}

void ProduceParts::PostUpdate()
{
}

void ProduceParts::Action()
{
	std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
	if (m_prodFlg)
	{
		std::shared_ptr<Missile> missile = std::make_shared<Missile>();
		missile->Init();
		missile->SetPlayer(spPlayer);
		SceneManager::Instance().AddObject(missile);

		std::shared_ptr<CleanRobot> robo = std::make_shared<CleanRobot>();
		robo->Init();
		robo->SetPlayer(spPlayer);
		SceneManager::Instance().AddObject(robo);

		m_prodFlg = false;
	}
}
