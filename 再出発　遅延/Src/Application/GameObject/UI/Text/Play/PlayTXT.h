#pragma once
#include"../../UIBase.h"
class Fade;

class PlayTXT :public UIBase
{
public:
	PlayTXT() {}
	~PlayTXT()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
	//連打防止
	bool m_key = false;
};
