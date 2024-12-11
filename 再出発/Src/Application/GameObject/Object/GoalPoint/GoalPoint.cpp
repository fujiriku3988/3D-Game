#include "GoalPoint.h"
#include"../../UI/UIBase.h"
#include"../../Camera/TPSCamera/TPSCamera.h"
#include"../../Character/Player/Player.h"

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

	m_filePath = _filePath;
}

void GoalPoint::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(false);
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color,{10,10,10});
	}
}

void GoalPoint::Update()
{
	if (m_hitFlg)
	{
		for (auto& m_wpUI : m_UIList)
		{
			if (std::shared_ptr<UIBase>spUI = m_wpUI.lock())
			{
				spUI->ToggleDraw();
			}
		}
		if (std::shared_ptr<TPSCamera>spCamera = m_wpCamera.lock())
		{
			spCamera->RotateMouseOFF();
		}
		if (std::shared_ptr<Player>spPlayer = m_wpPlayer.lock())
		{
			spPlayer->PlayerStopON();
		}
		m_hitFlg = false;
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void GoalPoint::PostUpdate()
{
}

void GoalPoint::Restart()
{
	Init(m_filePath);
}

void GoalPoint::AddUI(std::shared_ptr<UIBase> _ui)
{
	m_UIList.push_back(_ui);
}
