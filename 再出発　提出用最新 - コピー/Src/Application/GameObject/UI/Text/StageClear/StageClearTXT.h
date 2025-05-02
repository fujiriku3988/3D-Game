#pragma once
#include"../../UIBase.h"
class StageClearTXT :public UIBase
{
public:
	StageClearTXT() {}
	~StageClearTXT()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
