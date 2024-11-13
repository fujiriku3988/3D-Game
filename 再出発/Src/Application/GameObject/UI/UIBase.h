#pragma once
class UIBase :public KdGameObject
{
public:
	UIBase() {}
	~UIBase()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

protected:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_drawFlg = true;;
	int m_time;
	float m_alpha;
	float m_alphaMAX;
	float m_alphaMIN;
	float m_speed;
};