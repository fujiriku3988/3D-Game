#pragma once
class UIBase :public KdGameObject
{
public:
	UIBase() {}
	~UIBase()override {}

	virtual void Init(const std::string _string);
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
	int m_time = 0;
	float m_alpha = 1.0f;
	float m_alphaMAX = 1.0f;
	float m_alphaMIN = 0.3f;
};