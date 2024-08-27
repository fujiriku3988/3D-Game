#include "Light.h"

void Light::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Light/Light.gltf");
	m_pos = {};
	m_scale = { 0.5f };
	//m_color = { 1,1,1,1 };
	m_color = { 1,1,1,1 };
}

void Light::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, m_color);
}

void Light::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}
