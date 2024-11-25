#include "PressurePlate.h"
#include "../Fence/Fence.h"
#include"../../../Json/JsonManager.h"

void PressurePlate::Init()
{
	ObjectBase::Init();
	m_modelWork->SetModelData("Asset/Models/Terrain/PressurePlate/PressurePlate.gltf");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("upStand"));

	m_pos = { -5.0f,5.8f,8.0f };
	m_scale = { 0.8f };
	m_color = { 1.0f,1.0f,1.0f,1.0f };
	m_plateCT = 0;
	m_plateUp = true;
	m_plateDown = false;

	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "pos", m_pos);
	JsonManager::Instance().AddParamVec3("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "scale", m_scale);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "color", m_color);
	JsonManager::Instance().AddParam<int>("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "plateCT", m_plateCT);
	JsonManager::Instance().AddParam<bool>("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "plateUp", m_plateUp);
	JsonManager::Instance().AddParam<bool>("Asset/Data/Json/Stage1/PressurePlate/Plate.json", "Plate", "plateDown", m_plateDown);

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PressurePlate", m_modelWork, KdCollider::TypeEvent);
	m_objType = ePressurePlate;
}

void PressurePlate::Init(const std::string _filepath)
{
	ObjectBase::Init();
	m_modelWork->SetModelData("Asset/Models/Terrain/PressurePlate/PressurePlate.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filepath, "Plate", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filepath, "Plate", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filepath, "Plate", "color");
	m_plateCT = JsonManager::Instance().GetParam<int>(_filepath, "Plate", "plateCT");
	m_plateUp = JsonManager::Instance().GetParam<bool>(_filepath, "Plate", "plateUp");
	m_plateDown = JsonManager::Instance().GetParam<bool>(_filepath, "Plate", "plateDown");
	m_animState = JsonManager::Instance().GetParam<std::string>(_filepath, "Plate", "animation");
	m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation(m_animState));

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

void PressurePlate::AddFence(std::shared_ptr<Fence> _fence)
{
	if (_fence)
	{
		m_fences.push_back(_fence);
	}
}

void PressurePlate::PlayAnimation()
{
	std::shared_ptr<Fence>spFence = m_wpFence.lock();
	if (m_hitFlg)
	{
		if (m_plateDown == false)
		{
			m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("down"), false);
			for (auto& wpFence : m_fences)
			{
				if (std::shared_ptr<Fence>spFence = wpFence.lock())
				{
					spFence->ToggleRaise();
				}
			}
			if (spFence)
			{
				//spFence->ToggleRaise();
			}
			m_plateDown = true;
		}
	}

	if (m_plateUp == false)
	{
		m_animator->SetAnimation(m_modelWork->GetData()->GetAnimation("up"), false);
		m_plateUp = true;
	}

	if (m_plateDown == true)
	{
		m_plateCT++;
		if (m_plateCT >= 180)
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
