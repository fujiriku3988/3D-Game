#pragma once
#include"../UIBase.h"
class GameTime;

class Star :public UIBase
{
public:
	Star() {};
	~Star() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;

	void SetGameTime(const std::shared_ptr<GameTime> _time) { m_wpGameTime = _time; }
private:
	//色のRGBのみ
	Math::Vector3 m_rgb = {};
	//クリアしたか？true:してる、false:してない
	bool m_clearFlg = false;
	//エフェクト用
	//テクスチャ
	KdTexture m_effTex;
	//座標
	Math::Vector2 m_effPos = {};
	//色
	Math::Color m_effColor = {};
	//スケール
	Math::Vector2 m_effScale = {};
	//テクスチャサイズ
	Math::Vector2 m_effTexSize = {};
	//切り取り範囲
	Math::Rectangle m_effRect = {};
	//現在のアニメーション
	Math::Vector2 m_anim;
	//アニメーションのディレイ
	int m_animDelay = {};
	//クリア時間
	int m_clearTime = {};
	//アニメーションを行うか
	bool m_animFlg = false;
	//ゲーム時間の情報もらうよう
	std::weak_ptr<GameTime>m_wpGameTime;

	//SE鳴らすよう
	bool m_seFlg = false;
};
