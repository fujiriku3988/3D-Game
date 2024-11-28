#include "ObjectBase.h"
#include"../../Scene/SceneManager.h"

void ObjectBase::Init(const std::string _string)
{
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_animState = "NONE";

	m_animator = std::make_shared<KdAnimator>();
	m_modelData = std::make_shared<KdModelData>();
	m_modelWork = std::make_shared<KdModelWork>();
}

void ObjectBase::Init()
{
	m_pos = {};
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_animState = "NONE";

	m_animator = std::make_shared<KdAnimator>();
	m_modelData = std::make_shared<KdModelData>();
	m_modelWork = std::make_shared<KdModelWork>();
}

void ObjectBase::PreUpdate()
{
}

void ObjectBase::Update()
{
}

void ObjectBase::PostUpdate()
{
}

void ObjectBase::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
	if (m_modelData)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld, m_color);
	}
}

void ObjectBase::DrawSprite()
{
}

void ObjectBase::GenerateDepthMapFromLight()
{
}
