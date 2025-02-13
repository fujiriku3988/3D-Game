﻿#pragma once


class UIBase :public KdGameObject
{
public:
	UIBase() {}
	~UIBase()override {}

	virtual void Init(const std::string _filePath);
	void Init()override;
	void DrawSprite()override;
	void DrawUnLit()override;
	void Update()override;

	void ToggleDraw();
protected:
	//BGM,SEのスライダーの共有で使う
	//ポインターが必要なためここに置く
	static UIBase* m_activeSlider;

	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Color m_color;
	Math::Vector2 m_scale;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texSizeHarf;
	bool m_drawFlg = true;
	int m_time = 0;
	float m_alpha = 1.0f;
	float m_alphaMAX = 1.0f;
	float m_alphaMIN = 0.3f;
};