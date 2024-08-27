#pragma once
#include"../../UIBase.h"
class Work :public UIBase
{
public:
	Work() {}
	~Work()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
