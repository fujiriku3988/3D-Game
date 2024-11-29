#pragma once
#include"../../UIBase.h"

class KeyEnter :public UIBase
{
public:
	KeyEnter() {};
	~KeyEnter() {};

	void Init(const std::string _filePath)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
