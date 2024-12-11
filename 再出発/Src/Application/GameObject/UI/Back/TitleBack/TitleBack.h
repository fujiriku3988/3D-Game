#pragma once
#include"../../UIBase.h"
class TitleBack :public UIBase
{
public:
	TitleBack() {}
	~TitleBack()override {}

	void Init()override;
	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
};
