#pragma once
#include"../../UIBase.h"

class VolumeSliderBGM :public UIBase
{
public:
	VolumeSliderBGM() {};
	~VolumeSliderBGM() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

	void WirteJsonFile();
	void MoveHandle(const POINT _pos);
private:
	//背景テクスチャ
	KdTexture m_whiteSlideTex;
	//背景テクスチャ
	KdTexture m_blueSlideTex;
	//ハンドルテクスチャ
	KdTexture m_handleTex;

	//白いスライダー用変数
	//座標
	Math::Vector2 m_whitePos = {};
	//テクスチャサイズ
	Math::Vector2 m_whiteTexSize = {};
	//拡縮率
	Math::Vector2 m_whiteScale = {};
	//色
	Math::Color m_whiteColor = {};

	//青いスライダー用変数
	//座標
	Math::Vector2 m_bluePos = {};
	//テクスチャサイズ
	Math::Vector2 m_blueTexSize = {};
	//テクスチャサイズ（ハーフ）
	Math::Vector2 m_blueTexSizeHarf = {};
	//拡縮率
	Math::Vector2 m_blueScale = {};
	//色
	Math::Color m_blueColor = {};
	//描画補正値
	Math::Vector2 m_blueDrawAdjust = {};

	//ハンドル用変数
	//座標
	Math::Vector2 m_handlePos = {};
	//ハンドルの座標を記憶するよう
	Math::Vector2 m_handleCurrentPos = {};
	//テクスチャサイズ
	Math::Vector2 m_handleTexSize = {};
	//テクスチャサイズ
	Math::Vector2 m_handleTexSizeHarf = {};
	//拡縮率
	Math::Vector2 m_handleScale = {};
	//色
	Math::Color m_handleColor = {};

	//音量
	float m_volumeBGM;
	//一度だけSEの音出すよう
	bool m_volumeFlg = false;
};
