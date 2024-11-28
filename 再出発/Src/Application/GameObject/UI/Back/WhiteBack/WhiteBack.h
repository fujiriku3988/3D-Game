#pragma once
#include"../../UIBase.h"

class WhiteBack :public UIBase
{
public:
	WhiteBack() {};
	~WhiteBack() {};

	void Init(const std::string _string)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
