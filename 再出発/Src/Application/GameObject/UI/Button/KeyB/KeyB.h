﻿#pragma once
#include"../../UIBase.h"

class KeyB :public UIBase
{
public:
	KeyB() {};
	~KeyB() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
