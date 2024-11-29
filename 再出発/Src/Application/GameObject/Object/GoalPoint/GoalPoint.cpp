#include "GoalPoint.h"

void GoalPoint::Init(const std::string _filePath)
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Terrain/GoalPoint/GoalPoint.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "GoalPoint", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "GoalPoint", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "GoalPoint", "color");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("goal", m_modelWork, KdCollider::TypeEvent);
	m_objType = eGoalPoint;
}

void GoalPoint::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(false);
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color,{10,10,10});
		//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void GoalPoint::Update()
{
	if (m_hitFlg)
	{
		
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void GoalPoint::PostUpdate()
{
}
