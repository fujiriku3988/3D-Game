#include "TerrainBase.h"

void TerrainBase::Init()
{
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };

	m_animator = std::make_shared<KdAnimator>();
	m_modelData = std::make_shared<KdModelData>();
	m_modelWork = std::make_shared<KdModelWork>();
}

void TerrainBase::DrawLit()
{
	if (m_modelData)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
	}
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void TerrainBase::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void TerrainBase::PostUpdate()
{
}
