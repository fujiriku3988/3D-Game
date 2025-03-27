#pragma once
#include"../../UIBase.h"

class BackButton :public UIBase
{
public:
	BackButton() {};
	~BackButton() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	//連打防止
	bool m_key = false;
	//最大拡縮値
	float m_scaleMAX = {};
};
