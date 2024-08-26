#pragma once

class DevelopBar:public KdGameObject
{
public:
	DevelopBar() {}
	~DevelopBar()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

	void aliveFlgOff() { m_aliveFlg = false; }
private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_aliveFlg = true;
	float m_alpha;
};
