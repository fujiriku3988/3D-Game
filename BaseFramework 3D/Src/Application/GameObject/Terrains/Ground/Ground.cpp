#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tile/tile2.gltf");
	m_pos = {};
}

void Ground::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(10);
	m_mWorld = scaleMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
