#pragma once
#include"../ButtonBase.h"
class DevelopButton :public ButtonBase
{
public:
	DevelopButton() {}
	~DevelopButton()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
