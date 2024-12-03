#pragma once
#include"../../UIBase.h"

class Return :public UIBase
{
public:
	Return() {};
	~Return() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
};
