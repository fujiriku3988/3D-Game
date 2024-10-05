#include "CleanRobot.h"
#include"../../../Character/Player/Player.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../main.h"

void CleanRobot::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Structure/CleanRobot/cleanRobot.gltf");
	m_pos = { 2,1,0 };
	m_adjustHeight = -0.8f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("robot", m_modelWork, KdCollider::TypeDamage);
	m_objType = eBody;
}

void CleanRobot::Update()
{
	m_pos += m_dir * m_speed;
	//m_gravity += m_gravityPow;
	m_speed -= 0.1f;
	m_pos.y += -m_gravity;

	//CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	Math::Matrix playerMat;

	if (m_holdFlg)
	{
		m_gravity = 0;
		if (m_wpPlayer.expired() == false)
		{
			std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
			playerMat = Math::Matrix::CreateTranslation(spPlayer->GetPos());
			m_pos = spPlayer->GetPos();
			m_dir = spPlayer->GetMatrix().Backward();
			m_dir.Normalize();
		}
		//m_mWorld = transMat * playerMat;
		//m_mWorld = m_transMat;
	}
	else
	{
		//m_mWorld = m_transMat;
	}

	if (m_throwFlg)
	{
		m_speed = 1.0f;
		m_throwFlg = false;
	}

	if (m_speed <= 0)
	{
		m_speed = 0;
		//m_dir = {};
	}

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;
	AddNode();
	Application::Instance().m_log.Clear();
	//Application::Instance().m_log.AddLog("m_speed%f\n", m_speed);
	//Application::Instance().m_log.AddLog("m_dir%f\n", m_dir);
	//Application::Instance().m_log.AddLog("m_posX%f\n", m_pos.x);
	//Application::Instance().m_log.AddLog("m_posY%f\n", m_pos.y);
	//Application::Instance().m_log.AddLog("m_posZ%f\n", m_pos.z);
	//Application::Instance().m_log.AddLog("NODE%d\n", SceneManager::Instance().GetNodeList().size());//うまい事距離は取れてそう

}

void CleanRobot::AddNode()
{
	if (m_modelWork)
	{
		//blenderで作成したNULLポイントノードを探して取得
		//const KdModelWork::Node* pNode = m_modelWork->FindNode("Right");

		//指定ノードができたら
		//m_nodeMat = node->m_worldTransform * m_transMat;
		//node = m_modelWork->FindNode("Right");
		if (m_addNodeFlg)
		{
			m_pNode = m_modelWork->FindNode("Right");
			if (m_pNode) { SceneManager::Instance().AddNode(m_pNode); }
			m_pNode = m_modelWork->FindNode("Left");
			if (m_pNode) { SceneManager::Instance().AddNode(m_pNode); }
			m_addNodeFlg = false;
		}
	}
}
