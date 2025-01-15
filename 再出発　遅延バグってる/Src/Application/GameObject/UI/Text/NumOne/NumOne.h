#pragma once
#include"../../UIBase.h"
class NumOne :public UIBase
{
public:
	NumOne() {}
	~NumOne()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	bool m_key = false;
	Math::Vector2 m_anim;
	Math::Rectangle m_rect;
};
