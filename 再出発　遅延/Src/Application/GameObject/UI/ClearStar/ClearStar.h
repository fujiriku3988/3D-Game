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
	Math::Vector2 m_starPos;
	Math::Vector2 m_starTexSize;
	Math::Vector2 m_starScale;
	Math::Color m_starColor;
	std::string m_starFilePath;
};
