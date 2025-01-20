#pragma once
#include"../../UIBase.h"
class NumTwo :public UIBase
{
public:
	NumTwo() {}
	~NumTwo()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	bool m_key = false;
	Math::Vector2 m_anim;
	Math::Rectangle m_rect;
};
