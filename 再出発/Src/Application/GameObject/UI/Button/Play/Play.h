#pragma once
#include"../../UIBase.h"

class Play :public UIBase
{
public:
	Play() {};
	~Play() {};

	void Init(const std::string _filePath)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
};
