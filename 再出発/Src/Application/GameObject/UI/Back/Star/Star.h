#pragma once
#include"../../UIBase.h"

class Star :public UIBase
{
public:
	Star() {};
	~Star() {};

	void Init(const std::string _filePath)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
