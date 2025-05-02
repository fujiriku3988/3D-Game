#pragma once
#include"../../UIBase.h"

class TextFrame :public UIBase
{
public:
	TextFrame() {};
	~TextFrame() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
};
