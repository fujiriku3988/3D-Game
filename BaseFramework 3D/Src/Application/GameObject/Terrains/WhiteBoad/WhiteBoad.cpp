#include "WhiteBoad.h"
#include"../../../main.h"

void WhiteBoad::Init()
{
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Boad/Boad2.gltf");
	m_pos = {0,0,15};
	m_rot = {};
	m_key = false;
}

void WhiteBoad::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld);
}

void WhiteBoad::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (!m_key)
		{
			m_key = true;
			m_rot.y += 0.1;
		}
	}
	else
	{
		m_key = false;
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(3);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(4.7);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * rotMatY * transMat;

	/*Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("m_rotX:%f\n", m_rot.x);
	Application::Instance().m_log.AddLog("m_rotY:%f\n", m_rot.y);
	Application::Instance().m_log.AddLog("m_rotZ:%f\n", m_rot.z);
	Application::Instance().m_log.AddLog("m_rot:%f\n", m_rot);*/
}
