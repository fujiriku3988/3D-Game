#include "Fence.h"
#include"../../../Json/JsonManager.h"

void Fence::Init()
{
	/*TerrainBase::Init();

	m_modelWork->SetModelData("Asset/Models/Terrain/Fence/Fence2.gltf");

	m_pos = JsonManager::Instance().GetParamVec3("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "pos");
	m_scale = JsonManager::Instance().GetParamVec3("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "scale");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "color");
	m_animState = JsonManager::Instance().GetParam<std::string>("Asset/Data/Json/Stage1/Fence1.json", "Fence1", "animation");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Fence", m_modelWork, KdCollider::TypeBump);
	m_objType = eFence;*/
}

void Fence::Init(const std::string _filePath)
{
	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Terrain/Fence/Fence2.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "Fence", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "Fence", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Fence", "color");
	m_raise = JsonManager::Instance().GetParam<bool>(_filePath, "Fence", "raise");
	m_animState = JsonManager::Instance().GetParam<std::string>(_filePath, "Fence", "animation");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Fence", m_modelWork, KdCollider::TypeBump);
	m_objType = eFence;
}

void Fence::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void Fence::Update()
{
	//ToggleRaise();

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Fence::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void Fence::ToggleRaise()
{
	// 状態を反転
	m_raise = !m_raise;

	// 状態に応じて上げる・下げるアニメーションを再生
	if (m_raise)
	{
		Raise();
	}
	else 
	{
		Lower();
	}
}

void Fence::Raise()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"),false);
	}
}

void Fence::Lower()
{
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"),false);
	if (m_animator->IsAnimationEnd() == true)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downStand"),false);
	}
}
