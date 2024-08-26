#pragma once

class Perfect :public KdGameObject
{
public:
	Perfect() {}
	~Perfect()override {}

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
