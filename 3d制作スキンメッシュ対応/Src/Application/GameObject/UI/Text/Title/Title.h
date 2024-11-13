#pragma once
#include"../../UIBase.h"
class Title :public UIBase
{
public:
	Title() {}
	~Title()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
