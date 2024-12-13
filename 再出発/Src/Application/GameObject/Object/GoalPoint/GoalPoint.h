#pragma once
#include"../ObjectBase.h"

class UIBase;
class TPSCamera;
class Player;
class GameTime;

class GoalPoint :public ObjectBase
{
public:
	GoalPoint() {}
	~GoalPoint() override {}

	void Init(const std::string _filePath)override;
	void DrawLit()override;
	void Update()override;
	void PostUpdate()override;
	void Restart()override;

	void SetUI(const std::shared_ptr<UIBase> _ui) { m_wpUI = _ui; }
	void SetGameTime(const std::shared_ptr<GameTime> _time) { m_wpGameTime = _time; }
	void SetCamera(const std::shared_ptr<TPSCamera> _camera) { m_wpCamera = _camera; }
	void SetPlayer(const std::shared_ptr<Player> _player) { m_wpPlayer = _player; }
	void AddUI(const std::shared_ptr<UIBase> _fence);
private:
	std::weak_ptr<UIBase>m_wpUI;
	std::weak_ptr<GameTime>m_wpGameTime;
	std::weak_ptr<TPSCamera>m_wpCamera;
	std::weak_ptr<Player>m_wpPlayer;
	std::list<std::weak_ptr<UIBase>>m_UIList; //関連付けられたUIのリスト
};
