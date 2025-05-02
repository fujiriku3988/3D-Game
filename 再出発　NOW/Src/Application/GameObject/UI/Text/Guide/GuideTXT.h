#pragma once
#include"../../UIBase.h"
class Fade;
class UIBase;

class GuideTXT :public UIBase
{
public:
	GuideTXT() {}
	~GuideTXT()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	//連打防止
	bool m_key = false;
	//Fadeが終わっているなら0.0f,それ以外は続いてる
	float m_fadeAlpha = {};
	//透けさせるか true:透ける false:透けない
	bool m_fadeFlg = true;
};
