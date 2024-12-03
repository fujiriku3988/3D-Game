#pragma once
#include"../ObjectBase.h"

class UIBase;

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
	void AddUI(const std::shared_ptr<UIBase> _fence);
private:
	std::weak_ptr<UIBase>m_wpUI;
	std::list<std::weak_ptr<UIBase>> m_UIList; //関連付けられたUIのリスト

};
