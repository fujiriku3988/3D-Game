#pragma once

class Bad :public KdGameObject
{
public:
	Bad() {}
	~Bad()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	int m_time;
};
