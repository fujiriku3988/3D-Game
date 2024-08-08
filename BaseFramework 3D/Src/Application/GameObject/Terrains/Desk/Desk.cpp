#include "Desk.h"

void Desk::Init()
{
	m_pos = {};
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Desk/Desk.gltf");
}

void Desk::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(3);
	m_mWorld = scaleMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
