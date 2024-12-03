#include "Stage.h"

void Stage::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Terrain/Stage/Stage3.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Stage", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;

	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/Stage1.json","stage1","pos",m_pos);
	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/Stage1.json","stage1","scale",m_scale);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/Stage1/Stage1.json","stage1","color",m_color);
}

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
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
}