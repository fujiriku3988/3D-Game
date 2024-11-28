#pragma once
#include"../../UIBase.h"

class Frame :public UIBase
{
public:
	void Init(const std::string _string)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
