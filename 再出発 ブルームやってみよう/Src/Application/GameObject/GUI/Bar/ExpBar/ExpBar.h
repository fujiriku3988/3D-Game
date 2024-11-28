#pragma once
#include<string>

class ExpBar :public KdGameObject
{
public:
	ExpBar() {}
	~ExpBar()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;
	void ExpPointLoad();
	void ExpLoad();
	void ExpWrite();

	void WriteFlgOff() { m_writeFlg = true; }
private:
	KdTexture m_tex1;
	KdTexture m_tex2;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSizeMain;
	Math::Vector2 m_texSizeNull;
	Math::Vector2 m_pivot;
	float m_maxSizeMainX;
	int m_expPoint;
	int m_expPointUp;
	bool m_drawFlg = false;//falseが灰色trueが白色
	bool m_writeFlg = false;
};
