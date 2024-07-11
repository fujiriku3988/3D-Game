#include "Ground.h"

void Ground::Init()
{
	m_pos = {};
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");
}

void Ground::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(100);
	m_mWorld = scaleMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
