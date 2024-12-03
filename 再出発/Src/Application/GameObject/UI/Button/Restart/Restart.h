#pragma once
#include"../../UIBase.h"

class Restart :public UIBase
{
public:
	Restart() {};
	~Restart() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
};
