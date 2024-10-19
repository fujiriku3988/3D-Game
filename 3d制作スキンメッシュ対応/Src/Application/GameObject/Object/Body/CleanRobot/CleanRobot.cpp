#include "CleanRobot.h"
#include"../../../Character/Player/Player.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../main.h"

void CleanRobot::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Body/CleanRobot/cleanRobot.gltf");
	m_pos = { 2,1,0 };
	m_adjustHeight = 0.5f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("robot", m_modelWork, KdCollider::TypeDamage);
	m_objType = eBody;
}

void CleanRobot::Update()
{
	//ノード追加
	{
		AddNode();
	}
	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_speed -= 0.1f;
	m_pos.y += -m_gravity;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	if (m_holdFlg)
	{
		m_gravity = 0;
		if (m_wpPlayer.expired() == false)
		{
			for (auto& node : SceneManager::Instance().GetNodeList())
			{
				m_spPlayer = m_wpPlayer.lock();
				if (node->m_name == "hold")
				{
					m_pos = (node->m_worldTransform * m_spPlayer->GetMatrix()).Translation() + Math::Vector3(0,-1,0);
					m_rotationMat = m_spPlayer->GetRotationMatrix();
				}
			}
			//m_pos = m_spPlayer->GetPos();
			m_dir = m_spPlayer->GetMatrix().Backward();
			m_dir.Normalize();
		}
	}

	if (m_throwFlg)
	{
		m_speed = 1.0f;
		m_throwFlg = false;
	}

	if (m_speed <= 0)
	{
		m_speed = 0;
	}

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld =  m_transMat;
	//m_mWorld = m_rotationMat * m_transMat;
	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("ConnectCleanRobot:%d\n", m_connectedParts.size());
}

void CleanRobot::AddNode()
{
	//引数で値渡して使いやすくしてもいい
	if (m_modelWork)
	{
		if (m_addNodeFlg)
		{
			//ノード追加
			m_pNode = m_modelWork->FindNode("Right");
			if (m_pNode) { SceneManager::Instance().AddNode(m_pNode); }
			m_pNode = m_modelWork->FindNode("Left");
			if (m_pNode) { SceneManager::Instance().AddNode(m_pNode); }
			m_addNodeFlg = false;
		}
	}
}
