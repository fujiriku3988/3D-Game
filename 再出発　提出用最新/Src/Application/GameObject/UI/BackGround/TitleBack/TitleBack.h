#pragma once
#include"../../UIBase.h"

//タイトル画面に表示する背景
class TitleBack :public UIBase
{
public:
	TitleBack() {}
	~TitleBack()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
};
