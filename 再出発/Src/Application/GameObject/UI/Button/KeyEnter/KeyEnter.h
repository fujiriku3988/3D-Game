﻿#pragma once
#include"../../UIBase.h"

class KeyEnter :public UIBase
{
public:
	KeyEnter() {};
	~KeyEnter() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
