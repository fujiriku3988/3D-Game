#pragma once
#include"../ButtonBase.h"
class WorkButton :public ButtonBase
{
public:
	WorkButton() {}
	~WorkButton()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
