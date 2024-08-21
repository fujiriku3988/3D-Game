#pragma once
#include"../ButtonBase.h"
class SalesButton :public ButtonBase
{
public:
	SalesButton() {}
	~SalesButton()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
