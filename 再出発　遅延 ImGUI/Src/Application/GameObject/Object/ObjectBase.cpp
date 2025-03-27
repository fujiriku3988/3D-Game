#include "ObjectBase.h"
#include"../../Scene/SceneManager.h"

void ObjectBase::Init(const std::string _filePath)
{

}

void ObjectBase::Init(const std::string _filePath, int _id)
{
}

void ObjectBase::Init()
{
	m_emissive = {};
	m_pos = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/ObjectBase.json", "ObjectBase", "pos");
	m_scale = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/ObjectBase.json", "ObjectBase", "scale");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/BaseFile/ObjectBase.json", "ObjectBase", "color");
	m_animState = "NONE";
	m_objName = "";
	m_transMat = Math::Matrix::Identity;
	m_scaleMat = Math::Matrix::Identity;

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
	//モデル描画
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
