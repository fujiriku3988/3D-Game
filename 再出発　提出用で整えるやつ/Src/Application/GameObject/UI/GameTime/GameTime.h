﻿#pragma once
#include"../UIBase.h"

class GameTime :public UIBase
{
public:
	GameTime() {};
	~GameTime() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;

	//今の経過時間
	const int GetNowTime()const { return m_nowTime; }
	//時間を止める
	void StopTime() { m_startTimeFlg = false; }
	//時間の計測開始させる関数
	void StartTime();
private:
	//時間用変数
	struct time
	{
		Math::Vector2 secPosR = {};//秒単位・右座標
		Math::Vector2 secPosL = {};//秒単位・左座標
		Math::Vector2 minPosR = {};//分単位・右座標
		Math::Vector2 minPosL = {};//分単位・左座標

		Math::Rectangle secRectR = {};//秒単位・右切り取り範囲
		Math::Rectangle secRectL = {};//秒単位・左切り取り範囲
		Math::Rectangle minRectR = {};//分単位・右切り取り範囲
		Math::Rectangle minRectL = {};//分単位・左切り取り範囲

		Math::Vector2 secAnimR = {};//秒単位・現在のアニメーション
		Math::Vector2 secAnimL = {};//秒単位・現在のアニメーション
		Math::Vector2 minAnimR = {};//分単位・現在のアニメーション
		Math::Vector2 minAnimL = {};//分単位・現在のアニメーション
		
		Math::Vector2 texSize = {};
		Math::Vector2 scale = {};
		Math::Color color = {};
	};
	time m_time;

	//コロン用変数
	//テクスチャ
	KdTexture m_colonTex;
	//座標
	Math::Vector2 m_colonPos = {};
	//テクスチャサイズ
	Math::Vector2 m_colonTexSize = {};
	//スケール
	Math::Vector2 m_colonScale = {};
	//切り取り範囲
	Math::Rectangle m_colonRect = {};
	//色
	Math::Color m_colonColor = {};
	//現在のアニメーション
	Math::Vector2 m_colonAnim = {};

	//取得しやすいようにInt型の経過時間
	int m_nowTime = {};
	//経過時間を測るための変数
	std::chrono::steady_clock::time_point m_lastTime;
	//時間が開始されたか
	bool m_startTimeFlg = false;

};
