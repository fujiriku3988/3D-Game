#include "Stage.h"
void Stage::Init()
{
	TerrainBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Stage/stage.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_modelData, KdCollider::TypeGround);
	m_objType = eNone;
}
