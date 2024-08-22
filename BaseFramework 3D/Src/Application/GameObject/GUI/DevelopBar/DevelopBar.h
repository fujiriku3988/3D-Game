#pragma once

class DevelopBar:public KdGameObject
{
public:
	DevelopBar() {}
	~DevelopBar()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_drawFlg = false;//表示させるかのフラグ（実験用）
	bool m_rotFlg = false;//回転させるときの
};
