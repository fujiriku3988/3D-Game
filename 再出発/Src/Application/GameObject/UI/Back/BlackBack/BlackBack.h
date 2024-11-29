#pragma once
#include"../../UIBase.h"

class BlackBack :public UIBase
{
public:
	BlackBack() {};
	~BlackBack() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
private:
	KdTexture m_tex1;
	Math::Vector2 m_pos1;
	Math::Vector2 m_scale1;
	Math::Vector2 m_texSize1;
	Math::Color m_color1;
};
