#include "TerrainBase.h"

void TerrainBase::Init()
{
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_holdFlg = false;//使うかは未定（多分つかうはず）
}

void TerrainBase::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}

void TerrainBase::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}
