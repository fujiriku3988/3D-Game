#include "ProduceParts.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Object/Parts/Missile/Missile.h"
#include"../../../GameObject/Object/Body/CleanRobot/CleanRobot.h"
#include"../../../GameObject/Object/Container/Container.h"

void ProduceParts::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/ProduceParts/ProduceParts.gltf");
	m_pos = { -5.7,0,5 };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("ProduceParts", m_modelWork, KdCollider::TypeEvent|KdCollider::TypeBump);
	m_objType = eProduceParts;
	m_prodType = eNoneCont;
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
	int a = 0;
	std::shared_ptr<Player>m_spPlayer = m_wpPlayer.lock();
	std::shared_ptr<Container>m_spContainer = m_wpContainer.lock();
	ProductionType nowType = m_prodType;
	if (m_prodFlg)
	{
		switch (m_prodType)
		{
		case eMissile:
		{
			//ミサイル作る
			//関数化にしたい
			std::shared_ptr<ObjectBase> missile = std::make_shared<Missile>();
			missile->Init();
			missile->SetPos(m_pos + Math::Vector3(1, 2.0f, 0));
			missile->ChangeProdFlg(true);
			missile->SetContainer(m_spContainer);
			missile->SetPlayer(m_spPlayer);
			SceneManager::Instance().AddObject(missile);

			m_prodFlg = false;
			break;
		}
		case eCleanRobot:
		{
			std::shared_ptr<ObjectBase> cleanRobo = std::make_shared<CleanRobot>();
			cleanRobo->Init();
			cleanRobo->SetPos(m_pos + Math::Vector3(1, 2.0f, 0));
			cleanRobo->ChangeProdFlg(true);
			cleanRobo->SetContainer(m_spContainer);
			cleanRobo->SetPlayer(m_spPlayer);
			SceneManager::Instance().AddObject(cleanRobo);

			m_prodFlg = false;
			break;
		}
		}

	}
}
