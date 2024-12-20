﻿#include "GoalPoint.h"
#include"../../../Json/JsonManager.h"

void GoalPoint::Init()
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Terrain/GoalPoint/GoalPoint.gltf");

	m_pos = { 6,2,7 };
	m_scale = { 1.5f };
	m_color = { 1.5,1.5,1.5,1.5 };

	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/GoalPoint/GoalPoint.json", "GoalPoint", "pos", m_pos);
	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/GoalPoint/GoalPoint.json", "GoalPoint", "scale", m_scale);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/Stage1/GoalPoint/GoalPoint.json", "GoalPoint", "color", m_color);

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("goal", m_modelWork, KdCollider::TypeEvent);
	m_objType = eGoalPoint;
}

void GoalPoint::Init(const std::string _filepath)
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Terrain/GoalPoint/GoalPoint.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filepath, "GoalPoint", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filepath, "GoalPoint", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filepath, "GoalPoint", "color");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("goal", m_modelWork, KdCollider::TypeEvent);
	m_objType = eGoalPoint;
}

void GoalPoint::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(true);
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color,{100,100,100});
		//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
	//KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(false);
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
