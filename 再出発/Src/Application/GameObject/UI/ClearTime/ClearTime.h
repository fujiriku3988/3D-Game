#pragma once
#include"../UIBase.h"

class ClearTime :public UIBase
{
public:
	ClearTime() {};
	~ClearTime() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:
	//時間用変数
	struct time
	{
		Math::Vector2 secPosR;//秒単位・右座標
		Math::Vector2 secPosL;//秒単位・左座標
		Math::Vector2 minPosR;//分単位・右座標
		Math::Vector2 minPosL;//分単位・左座標

		Math::Rectangle secRectR;//秒単位・右切り取り範囲
		Math::Rectangle secRectL;//秒単位・左切り取り範囲
		Math::Rectangle minRectR;//分単位・右切り取り範囲
		Math::Rectangle minRectL;//分単位・左切り取り範囲

		Math::Vector2 secAnimR;//秒単位・現在のアニメーション
		Math::Vector2 secAnimL;//秒単位・現在のアニメーション
		Math::Vector2 minAnimR;//分単位・現在のアニメーション
		Math::Vector2 minAnimL;//分単位・現在のアニメーション

		Math::Vector2 texSize;
		Math::Vector2 scale;
		Math::Color color;
	};
	time m_time;

	//星の評価するやつ
	KdTexture m_starTex;
	Math::Vector2 m_starPos;
	Math::Vector2 m_starTexSize;
	Math::Vector2 m_starScale;
	Math::Color m_starColor;
	std::string m_starFilePath;

	//コロン用変数
	KdTexture m_colonTex;
	Math::Vector2 m_colonPos;
	Math::Vector2 m_colonTexSize;
	Math::Vector2 m_colonScale;
	Math::Rectangle m_colonRect;
	Math::Color m_colonColor;
	Math::Vector2 m_colonAnim;//現在のアニメーション
};
