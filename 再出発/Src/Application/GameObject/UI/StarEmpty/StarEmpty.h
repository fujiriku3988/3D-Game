#pragma once
#include"../UIBase.h"

class StarEmpty :public UIBase
{
public:
	StarEmpty() {};
	~StarEmpty() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
};
