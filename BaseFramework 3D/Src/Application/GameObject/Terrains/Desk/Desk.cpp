#include "Desk.h"

void Desk::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Desk/Desk.gltf");
	m_pos = {};
}

void Desk::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(5);
	m_mWorld = scaleMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
