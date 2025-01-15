#pragma once
#include"../../UIBase.h"

class RestartButton :public UIBase
{
public:
	RestartButton() {};
	~RestartButton() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
	//連打防止
	bool m_keyFlg = false;
	float m_scaleMAX = 1.2f;
};
