#pragma once
#include"../UIBase.h"

class GuideBoard :public UIBase
{
public:
	GuideBoard() {};
	~GuideBoard() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
