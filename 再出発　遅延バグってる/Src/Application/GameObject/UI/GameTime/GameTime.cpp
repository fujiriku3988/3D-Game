#include "GameTime.h"
#include"../../../main.h"

void GameTime::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/number.png");
	m_time.secPosR = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "secPosR");
	m_time.secPosL = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "secPosL");
	m_time.minPosR = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "minPosR");
	m_time.minPosL = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "minPosL");

	m_time.secAnimR = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "secAnimR");
	m_time.secAnimL = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "secAnimL");
	m_time.minAnimR = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "minAnimR");
	m_time.minAnimL = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "minAnimL");

	m_time.scale = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "timeScale");
	m_time.texSize = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "timeTexSize");
	m_time.color = JsonManager::Instance().GetParamVec4(_filePath, "GameTime", "timeColor");

	//コロン
	m_colonTex.Load("Asset/Textures/UI/Text/colon.png");
	m_colonPos = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "colonPos");
	m_colonScale = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "colonScale");
	m_colonTexSize = JsonManager::Instance().GetParamVec2(_filePath, "GameTime", "colonTexSize");
	m_colonColor = JsonManager::Instance().GetParamVec4(_filePath, "GameTime", "colonColor");
	m_frame = JsonManager::Instance().GetParam<int>("Asset/Data/Json/UI/GameTime/GameTime.json", "GameTime", "frame");
	m_nowTime = JsonManager::Instance().GetParam<int>("Asset/Data/Json/UI/GameTime/GameTime.json", "GameTime", "nowTime");
	m_timeFlg = JsonManager::Instance().GetParam<bool>("Asset/Data/Json/UI/GameTime/GameTime.json", "GameTime", "timeFlg");

	m_filePath = _filePath;
}

void GameTime::DrawSprite()
{
	m_time.secRectR = { (long)m_time.texSize.x * (long)m_time.secAnimR.x,(long)m_time.texSize.y * (long)m_time.secAnimR.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.secRectL = { (long)m_time.texSize.x * (long)m_time.secAnimL.x,(long)m_time.texSize.y * (long)m_time.secAnimL.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.minRectR = { (long)m_time.texSize.x * (long)m_time.minAnimR.x,(long)m_time.texSize.y * (long)m_time.minAnimR.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.minRectL = { (long)m_time.texSize.x * (long)m_time.minAnimL.x,(long)m_time.texSize.y * (long)m_time.minAnimL.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_colonRect = { {},{},(long)m_colonTexSize.x ,(long)m_colonTexSize.y };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_time.secPosR.x, (int)m_time.secPosR.y,
		(int)m_time.texSize.x * (int)m_time.scale.x, (int)m_time.texSize.y * (int)m_time.scale.y, &m_time.secRectR, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_time.secPosL.x, (int)m_time.secPosL.y,
		(int)m_time.texSize.x * (int)m_time.scale.x, (int)m_time.texSize.y * (int)m_time.scale.y, &m_time.secRectL, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_time.minPosR.x, (int)m_time.minPosR.y,
		(int)m_time.texSize.x * (int)m_time.scale.x, (int)m_time.texSize.y * (int)m_time.scale.y, &m_time.minRectR, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_time.minPosL.x, (int)m_time.minPosL.y,
		(int)m_time.texSize.x * (int)m_time.scale.x, (int)m_time.texSize.y * (int)m_time.scale.y, &m_time.minRectL, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_colonTex, (int)m_colonPos.x, (int)m_colonPos.y,
		(int)m_colonTexSize.x * (int)m_colonScale.x, (int)m_colonTexSize.y * (int)m_colonScale.y, &m_colonRect, &m_colonColor);

}

void GameTime::Update()
{
	if (m_timeFlg)
	{
		m_frame++;
	}
	else
	{
		//秒単位・右
		//m_time.secPosR = { 70,-50 };
		//秒単位・左
		//m_time.secPosL = { 40,-50 };
		//分単位・右
		//m_time.minPosR = { -10,-50 };
		//分単位・右
		//m_time.minPosL = { -40,-50 };
		//コロン
		//m_colonPos = { 5,-30 };
	}

	if (m_frame > 60)
	{
		m_nowTime++;
		m_time.secAnimR.x++;
		m_frame = 0;
	}

	if (m_time.secAnimR.x > 9)
	{
		m_time.secAnimR.x = 0;
		m_time.secAnimL.x++;
	}
	if (m_time.secAnimL.x >= 6)
	{
		m_time.secAnimL.x = 0;
		m_time.minAnimR.x++;
	}
}

void GameTime::Restart()
{
	Init(m_filePath);
}
