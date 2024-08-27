#pragma once
#include"../../UIBase.h"
class Great :public UIBase
{
public:
	Great() {}
	~Great()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
