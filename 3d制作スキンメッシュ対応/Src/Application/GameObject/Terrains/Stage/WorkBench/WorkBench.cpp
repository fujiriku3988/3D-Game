#include "WorkBench.h"
void WorkBench::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Stage/WorkBench/WorkBench.gltf");
	m_pos = {0.0f,-0.0f,-5.0f};
	m_scale = { 1.5f };
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("WorkBench", m_modelData, KdCollider::TypeBump);
	m_objType = eNone;
}

void WorkBench::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}
