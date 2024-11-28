#pragma once
#include"../UIBase.h"

class ButtonFrame :public UIBase
{
public:
	ButtonFrame() {};
	~ButtonFrame() {};

	void Init(const std::string _filePath)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
