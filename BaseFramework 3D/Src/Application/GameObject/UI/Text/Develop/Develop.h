#pragma once
#include"../../UIBase.h"
class Develop :public UIBase
{
public:
	Develop() {}
	~Develop()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
