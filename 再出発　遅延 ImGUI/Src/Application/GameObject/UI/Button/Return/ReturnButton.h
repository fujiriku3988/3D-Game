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
	//scaleの最大値
	float m_scaleMAX = {};
	//連打防止
	bool m_keyFlg = false;
	//連打防止
	bool m_mouseKeyFlg = false;
};
