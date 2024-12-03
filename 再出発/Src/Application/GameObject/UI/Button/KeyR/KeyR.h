#pragma once
#include"../../UIBase.h"

class KeyR :public UIBase
{
public:
	KeyR() {};
	~KeyR() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
};
