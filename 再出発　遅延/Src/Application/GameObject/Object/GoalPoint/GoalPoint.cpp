﻿#include "GoalPoint.h"
#include"../../UI/UIBase.h"
#include"../../UI/GameTime/GameTime.h"
#include"../../Camera/TPSCamera/TPSCamera.h"
#include"../../Character/Player/Player.h"
#include"../../../../Framework/Effekseer/KdEffekseerManager.h"
#include"../../../main.h"

void GoalPoint::Init(const std::string _filePath)
{
	if (m_cursorFlg == true)
	{
		ShowCursor(false);
	}

	ObjectBase::Init();

	m_modelWork->SetModelData("Asset/Models/Object/GoalPoint/GoalPoint.gltf");

	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "GoalPoint", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "GoalPoint", "scale");
	m_emissive = JsonManager::Instance().GetParamVec3(_filePath, "GoalPoint", "emissive");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "GoalPoint", "color");
	m_effSize= JsonManager::Instance().GetParam<float>(_filePath, "GoalPoint", "effSize");
	m_effSpeed= JsonManager::Instance().GetParam<float>(_filePath, "GoalPoint", "effSpeed");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("goal", m_modelWork, KdCollider::TypeEvent);
	m_objType = eGoalPoint;

	m_hitFlg = false;
	m_cursorFlg = false;

	m_filePath = _filePath;

	m_wpEffekseer = KdEffekseerManager::GetInstance().Play("GoalPoint.efkefc", m_pos , m_effSize, m_effSpeed, true);
}

void GoalPoint::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.SetEmissiveEnable(false);
	if (m_modelWork)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color, m_emissive);
	}
}

void GoalPoint::Update()
{
	if (m_hitFlg)
	{
		ShowCursorIfNeeded();

		for (auto& m_wpUI : m_UIList)
		{
			if (std::shared_ptr<UIBase>spUI = m_wpUI.lock())
			{
				spUI->ToggleDraw();
			}	
		}
		if (std::shared_ptr<GameTime>spGameTime = m_wpGameTime.lock())
		{
			spGameTime->StopTime();
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
	
	std::shared_ptr<KdEffekseerObject> spEff = m_wpEffekseer.lock();
	if (spEff)
	{
		//エフェクトを止める
		spEff->StopEffect();
	}
}

void GoalPoint::ShowCursorIfNeeded()
{
	if (!m_cursorFlg)  // カーソルが非表示の場合のみ表示する
	{
		ShowCursor(true);
		m_cursorFlg = true;
	}
}

void GoalPoint::AddUI(std::shared_ptr<UIBase> _ui)
{
	m_UIList.push_back(_ui);
}
