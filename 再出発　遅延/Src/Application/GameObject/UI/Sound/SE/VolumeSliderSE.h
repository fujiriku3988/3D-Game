#pragma once
#include"../../UIBase.h"

class VolumeSliderSE :public UIBase
{
public:
	VolumeSliderSE() {};
	~VolumeSliderSE()
	{
		if (m_activeSlider == this) 
		{
			m_activeSlider = nullptr;
		}
	}

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;

	//jsonに書きこむ関数
	void WirteJsonFile();
	//ハンドルを操作する関数
	void MoveHandle(const POINT _pos);
private:
	//スライダーが干渉しないようにするための変数
	//操作中のスライダー
	//static VolumeSliderSE* m_activeSlider;

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

	//ドラッグ状態か
	bool m_dragFlg = false;
};
