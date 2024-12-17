#include "Stage.h"

void Stage::Init(const std::string _filePath)
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Terrain/Stage/Stage3.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "stage1", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "stage1", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "stage1", "color");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Stage", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;

	KdEffekseerManager::GetInstance().Play("BackLight.efkefc", m_pos , 2, 1, true);
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}