#include "PressurePlateBase.h"
#include "../Fence/Fence.h"

void PressurePlateBase::Init(const std::string _filePath)
{
}

void PressurePlateBase::Init()
{
	ObjectBase::Init();

	m_plateCT = {};
	m_plateUp = true;
	m_plateDown = false;
	m_hitFlg = false;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PressurePlate", m_modelWork, KdCollider::TypeEvent);
	m_objType = ePressurePlate;
}

void PressurePlateBase::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void PressurePlateBase::Update()
{
	PlayAnimation();

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void PressurePlateBase::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void PressurePlateBase::Restart()
{
}

void PressurePlateBase::PlayAnimation()
{

}
