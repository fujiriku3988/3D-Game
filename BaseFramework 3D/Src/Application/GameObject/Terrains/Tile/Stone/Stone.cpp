﻿#include "Stone.h"

void Stone::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tile/tile2.gltf");
	m_pos = {};
	m_scale = { 0.7f };
	//m_color = { 1,1,1,1 };
	m_color = { 4,4,4,1 };
}

void Stone::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, m_color);
}

void Stone::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}
