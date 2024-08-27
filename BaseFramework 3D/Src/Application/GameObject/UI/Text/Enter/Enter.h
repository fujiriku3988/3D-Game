#pragma once
#include"../../UIBase.h"
class Enter :public UIBase
{
public:
	Enter() {}
	~Enter()override {}

	void Init()override;
	void DrawSprite()override;
	void Update()override;

private:
	float m_alpha = 1.0f;
	float m_alphaMax = 360.0f;
	float m_alphaMin = 0.3f;
	float m_alphaSpeed = 2.0f;
	bool m_keyFlg = false;
};
