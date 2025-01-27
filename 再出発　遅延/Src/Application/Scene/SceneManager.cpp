﻿#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "GameScene/Stage1/StageScene1.h"
#include "GameScene/Stage2/StageScene2.h"
#include "StageSelectScene/StageSelectScene.h"
#include "SettingScene/SettingScene.h"
#include "GuideScene/GuideScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_currentScene->AddObject(obj);
}


void SceneManager::ChangeScene(SceneType sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneType::SettingScene:
		m_currentScene = std::make_shared<SettingScene>();
		break;
	case SceneType::GuideScene:
		m_currentScene = std::make_shared<GuideScene>();
		break;
	case SceneType::StageSelectScene:
		m_currentScene = std::make_shared<StageSelectScene>();
		break;
	case SceneType::Stage1:
		m_currentScene = std::make_shared<StageScene1>();
		break;
	case SceneType::Stage2:
		m_currentScene = std::make_shared<StageScene2>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}
