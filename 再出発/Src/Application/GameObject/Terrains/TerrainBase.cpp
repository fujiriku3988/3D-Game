﻿#include "TerrainBase.h"

void TerrainBase::Init(const std::string _string)
{
}

void TerrainBase::Init()
{
	m_pos = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/TerrainBase.json", "TerrainBase", "pos");
	m_scale = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/TerrainBase.json", "TerrainBase", "scale");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/BaseFile/TerrainBase.json", "TerrainBase", "color");
	m_transMat = Math::Matrix::Identity;
	m_scaleMat = Math::Matrix::Identity;

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
