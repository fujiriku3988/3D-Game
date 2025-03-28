﻿#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "GameDevelop/GameDevelop.h"
#include "StageSelectScene/StageSelectScene.h"
#include"ResultScene/ResultDevelop/ResultDevelop.h"

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

//void SceneManager::AddNode(const std::shared_ptr<KdModelWork::Node>& node)
//{
//	m_currentScene->AddNode(node);
//}

void SceneManager::AddNode(const KdModelWork::Node*& node)
{
	m_currentScene->AddNode(node);
}

//const std::list<std::shared_ptr<KdModelWork::Node>>& SceneManager::GetNodeList()
//{
//	return m_currentScene->GetNodeList();
//}

const std::list<const KdModelWork::Node*>& SceneManager::GetNodeList()
{
	return m_currentScene->GetNodeList();
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
	case SceneType::StageSelectScene:
		m_currentScene = std::make_shared<StageSelectScene>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}
