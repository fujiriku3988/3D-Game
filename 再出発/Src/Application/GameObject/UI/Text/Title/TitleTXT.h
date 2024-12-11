#pragma once
#include"../../UIBase.h"
class TitleTXT :public UIBase
{
public:
	TitleTXT() {}
	~TitleTXT()override {}

	void Init()override;
	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
};
