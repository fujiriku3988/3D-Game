#include "Stage.h"

void Stage::Init(const std::string _filePath, const std::string _stage)
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Terrain/" + _stage + "/Stage.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, _stage, "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, _stage, "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, _stage, "color");
	m_effSize = JsonManager::Instance().GetParam<float>(_filePath, _stage, "effSize");
	m_effSpeed = JsonManager::Instance().GetParam<float>(_filePath, _stage, "effSpeed");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Stage", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;

	KdEffekseerManager::GetInstance().Play("BackLight.efkefc", m_pos, m_effSize, m_effSpeed, true);
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}