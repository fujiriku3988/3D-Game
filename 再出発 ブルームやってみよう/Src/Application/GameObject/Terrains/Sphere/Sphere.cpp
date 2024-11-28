#include "Sphere.h"
void Sphere::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Terrain/Sphere/Sphere2.gltf");
	m_pos = {};
	m_scale = { 3.0f };
	m_color = { 2,2,2,2 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Sphere", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;
}

void Sphere::Update()
{
	
	m_uvOffset.x += 0.00001f;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Sphere::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetUVOffset(m_uvOffset);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}

void Sphere::DrawBright()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}
