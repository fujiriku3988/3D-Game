#pragma once
#include"../../UIBase.h"
class Sales :public UIBase
{
public:
	Sales() {}
	~Sales()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
