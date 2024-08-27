#pragma once
#include"../RobotGUIBase.h"
class BodyGUI :public RobotGUIBase
{
public:
	BodyGUI() {}
	~BodyGUI()override {}

	void Init()override;
	void DrawSprite()override;
private:
};
