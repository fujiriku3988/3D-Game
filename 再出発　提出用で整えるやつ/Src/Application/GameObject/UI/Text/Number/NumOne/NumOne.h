#pragma once
#include"../../../UIBase.h"
class NumOne :public UIBase
{
public:
	NumOne() {}
	~NumOne()override {}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

private:
	//連打防止
	bool m_key = false;
	//アニメーションの位置（スプレッドシート）
	Math::Vector2 m_anim;
	//切り取り範囲
	Math::Rectangle m_rect;
};
