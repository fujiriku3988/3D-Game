#pragma once
#include"../../UIBase.h"
class PlayTXT :public UIBase
{
public:
	PlayTXT() {}
	~PlayTXT()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	bool m_key = false;
};
