#pragma once
#include"../UIBase.h"

class Star :public UIBase
{
public:
	Star() {};
	~Star() {};

	void Init(const std::string _filePath)override;
	void Init()override;
	void DrawSprite()override;
	void Update()override;
private:
	bool a = true;

	KdTexture m_tex1;
	Math::Vector2 m_pos1;
	Math::Color m_color1;
	Math::Vector2 m_scale1;
	Math::Vector2 m_texSize1;
	Math::Rectangle m_rect1;
	Math::Vector2 m_anim;
	float m_alpha1=1.0f;
};
