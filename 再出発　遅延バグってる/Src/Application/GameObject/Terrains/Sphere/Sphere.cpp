#include "Sphere.h"

void Sphere::Init(const std::string _filePath)
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Terrain/SkyBox/skybox.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "Sphere", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "Sphere", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Sphere", "color");

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
	KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(false);
	KdShaderManager::Instance().m_StandardShader.SetUVOffset(m_uvOffset);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color,{100,100,100});
}
