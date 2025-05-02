#pragma once
#include"../../UIBase.h"

class StageFrame :public UIBase
{
public:
	StageFrame() {};
	~StageFrame() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
};
