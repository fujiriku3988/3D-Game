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

	//経過時間初期化
	m_nowTime = {};
	//現在の最初の時間
	m_lastTime = std::chrono::steady_clock::now(); 
	//時間が開始されたか
	m_startTimeFlg = false;

	m_filePath = _filePath;
}

void GameTime::DrawSprite()
{
	//描画範囲
	m_time.secRectR = { (long)m_time.texSize.x * (long)m_time.secAnimR.x,(long)m_time.texSize.y * (long)m_time.secAnimR.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.secRectL = { (long)m_time.texSize.x * (long)m_time.secAnimL.x,(long)m_time.texSize.y * (long)m_time.secAnimL.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.minRectR = { (long)m_time.texSize.x * (long)m_time.minAnimR.x,(long)m_time.texSize.y * (long)m_time.minAnimR.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_time.minRectL = { (long)m_time.texSize.x * (long)m_time.minAnimL.x,(long)m_time.texSize.y * (long)m_time.minAnimL.y,
				(long)m_time.texSize.x ,(long)m_time.texSize.y };

	m_colonRect = { {},{},(long)m_colonTexSize.x ,(long)m_colonTexSize.y };
	
	//描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.secPosR.x, m_time.secPosR.y,
		m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.secRectR, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.secPosL.x, m_time.secPosL.y,
		m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.secRectL, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.minPosR.x, m_time.minPosR.y,
		m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.minRectR, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.minPosL.x, m_time.minPosL.y,
		m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.minRectL, &m_time.color);

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_colonTex, m_colonPos.x, m_colonPos.y,
		m_colonTexSize.x * m_colonScale.x, m_colonTexSize.y * m_colonScale.y, &m_colonRect, &m_colonColor);

}

void GameTime::Update()
{
	// 時間関連の定数
	constexpr int MaxSeconds = 9;        //秒の1桁目の最大値
	constexpr int MaxTensOfSeconds = 5;  //秒の10桁目の最大値
	constexpr int MaxMinutes = 9;        //分の1桁目の最大値
	constexpr int MaxTensOfMinutes = 5;  //分の10桁目の最大値

	if (m_startTimeFlg == false) { return; }

	//現在の時間取得
	auto realTime = std::chrono::steady_clock::now();
	//経過時間
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(realTime - m_lastTime).count();

	if (elapsedTime >= NumberConstants::NumOne)  //1秒ごとに時間を進める
	{
		//時間リセット
		m_lastTime = realTime;
		m_nowTime++;

		// 秒単位の更新
		m_time.secAnimR.x++;
		if (m_time.secAnimR.x > MaxSeconds)
		{
			m_time.secAnimR.x = NumberConstants::NumZero;
			m_time.secAnimL.x++;
		}

		// 10秒単位の更新
		if (m_time.secAnimL.x > MaxTensOfSeconds)
		{
			m_time.secAnimL.x = NumberConstants::NumZero;
			m_time.minAnimR.x++;
		}

		// 分単位の更新
		if (m_time.minAnimR.x > MaxMinutes)
		{
			m_time.minAnimR.x = NumberConstants::NumZero;
			m_time.minAnimL.x++;
		}

		// 10分単位の更新
		if (m_time.minAnimL.x > MaxTensOfMinutes)
		{
			m_time.minAnimL.x = NumberConstants::NumZero;
		}
	}
}

void GameTime::Restart()
{
	//リスタート
	Init(m_filePath);
}

void GameTime::StartTime()
{
	m_startTimeFlg = true;
	m_lastTime = std::chrono::steady_clock::now();
}
