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
	Math::Vector3 m_rgb = {};
	bool m_clearFlg = false;
	//エフェクト用
	KdTexture m_effTex;
	Math::Vector2 m_effPos = {};
	Math::Color m_effColor = {};
	Math::Vector2 m_effScale = {};
	Math::Vector2 m_effTexSize = {};
	Math::Rectangle m_effRect = {};
	Math::Vector2 m_anim;//現在のアニメーション
	int m_animDelay = {};//アニメーションのディレイ
	int m_clearTime = {};//クリア時間
	bool m_animFlg = false;//アニメーションを行うか
	std::weak_ptr<GameTime>m_wpGameTime;

	//SE鳴らすよう
	bool m_seFlg = false;
};
