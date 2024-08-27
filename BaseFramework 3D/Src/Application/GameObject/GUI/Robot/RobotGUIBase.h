#pragma once
class RobotGUIBase :public KdGameObject
{
public:
	RobotGUIBase() {}
	~RobotGUIBase()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

	void DrawFlgOn() { m_drawFlg = true; }
	void AliveFlgOff() { m_aliveFlg = false; }
protected:
	KdTexture m_tex1;
	KdTexture m_tex2;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	bool m_drawFlg = false;//falseが灰色trueが白色
	bool m_aliveFlg = false;
	float m_alpha = 1.0f;
	float m_alphaMax = 360.0f;
	float m_alphaMin = 0;
	float m_alphaSpeed = 2.0f;
};