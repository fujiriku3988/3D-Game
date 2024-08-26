#pragma once

class Enter :public KdGameObject
{
public:
	Enter() {}
	~Enter()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_keyFlg = false;//キー制御
	float m_alpha;
	float m_alphaMax;
	float m_alphaMin;
	float m_alphaSpeed;
};
