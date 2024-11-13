#include "Sphere.h"
void Sphere::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Stage/Sphere/Sphere.gltf");
	m_pos = {};
	m_scale = { 3.0f };
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("TiSpherele", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;
}

void Sphere::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}
