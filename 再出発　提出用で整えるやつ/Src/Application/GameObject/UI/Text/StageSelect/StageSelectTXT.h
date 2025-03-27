#pragma once
#include"../../UIBase.h"
class StageSelectTXT :public UIBase
{
public:
	StageSelectTXT() {}
	~StageSelectTXT()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	//連打防止
	bool m_key = false;
	//Fadeが終わっているなら0.0f,それ以外は続いてる
	float m_fadeAlpha = {};
};
