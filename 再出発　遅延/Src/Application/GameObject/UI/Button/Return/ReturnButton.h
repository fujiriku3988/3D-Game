#pragma once
#include"../../UIBase.h"

class ReturnButton :public UIBase
{
public:
	ReturnButton() {};
	~ReturnButton() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
	float m_scaleMAX = 1.2f;
};
