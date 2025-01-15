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
};
