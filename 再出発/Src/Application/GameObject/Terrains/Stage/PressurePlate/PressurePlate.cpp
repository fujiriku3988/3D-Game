#include "PressurePlate.h"
void PressurePlate::Init()
{
	TerrainBase::Init();
	m_modelWork->SetModelData("Asset/Models/Stage/PressurePlate/PressurePlate.gltf");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"));

	m_pos = { -5,5.8f,6 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PressurePlate", m_modelWork, KdCollider::TypeEvent);
	m_objType = ePressurePlate;
}

void PressurePlate::DrawLit()
{
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
	}
}

void PressurePlate::Update()
{
	PlayAnimation();


	if (GetAsyncKeyState('1'))
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"), false);
		if (m_animator->IsAnimationEnd() == true)
		{
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downStand"));
		}
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void PressurePlate::PostUpdate()
{
	//アニメーションの更新
	m_animator->AdvanceTime(m_modelWork->WorkNodes());
	m_modelWork->CalcNodeMatrices();
}

void PressurePlate::PlayAnimation()
{
	if (m_hitFlg)
	{
		if (m_plateDown == false)
		{
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"), false);
			if (m_animator->IsAnimationEnd() == true)
			{
				m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("downStand"), false);
			}
			m_plateDown = true;
		}
	}

	if (m_plateUp == false)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"), false);
		if (m_animator->IsAnimationEnd() == true)
		{
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"), false);
		}
		m_plateUp = true;
	}

	if (m_plateDown == true)
	{
		m_plateCT++;
		if (m_plateCT >= 60)
		{
			m_hitFlg = false;
			m_plateUp = false;
			m_plateDown = false;
		}
	}
	else
	{
		m_plateCT = 0;
	}
}
