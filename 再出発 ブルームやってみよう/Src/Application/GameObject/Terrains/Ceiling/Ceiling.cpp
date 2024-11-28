﻿#include "Ceiling.h"
void Ceiling::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Stage/Ceiling/Ceiling.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ceiling", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;
}

void Ceiling::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 3,3 });
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}
