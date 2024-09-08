#include "Carpet.h"

void Carpet::Init()
{
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Tile/tile2.gltf");
	m_pos = {};
	m_scale = { 0.7f };
	//m_color = { 1,1,1,1 };
	m_color = { 4,4,4,1 };
}

void Carpet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}

void Carpet::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}
