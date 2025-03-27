#pragma once
#include"../../UIBase.h"

//UIを表示する時に使う背景
class UIBack :public UIBase
{
public:
	UIBack() {}
	~UIBack()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
};
