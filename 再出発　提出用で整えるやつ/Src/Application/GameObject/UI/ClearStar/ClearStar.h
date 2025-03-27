#pragma once
#include"../UIBase.h"

class ClearStar :public UIBase
{
public:
	ClearStar() {};
	~ClearStar() {};

	void Init(const std::string _filePath)override;
	void DrawSprite()override;
	void Update()override;
	void Restart()override;
private:

	//星の評価するやつ
	KdTexture m_starTex;
	//座標
	Math::Vector2 m_starPos;
	//テクスチャサイズ
	Math::Vector2 m_starTexSize;
	//スケール
	Math::Vector2 m_starScale;
	//色
	Math::Color m_starColor;
	//スターの画像パス
	std::string m_starFilePath;
};
