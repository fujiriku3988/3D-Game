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
	//連打防止
	bool m_mouseKeyFlg = false;
	//scaleの最大値
	float m_scaleMAX = {};
};
