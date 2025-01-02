#pragma once
#include"../../UIBase.h"
class Enter :public UIBase
{
public:
	Enter() {}
	~Enter()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
};
