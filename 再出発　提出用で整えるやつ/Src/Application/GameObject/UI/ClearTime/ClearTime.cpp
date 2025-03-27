#include "ClearTime.h"
#include"../../../main.h"

void ClearTime::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/number.png");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "ClearTime", "drawFlg");
	m_time.secPosR = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "secPosR");
	m_time.secPosL = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "secPosL");
	m_time.minPosR = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "minPosR");
	m_time.minPosL = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "minPosL");

	m_time.secAnimR = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "secAnimR");
	m_time.secAnimL = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "secAnimL");
	m_time.minAnimR = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "minAnimR");
	m_time.minAnimL = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "minAnimL");

	m_time.scale = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "timeScale");
	m_time.texSize = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "timeTexSize");
	m_time.color = JsonManager::Instance().GetParamVec4(_filePath, "ClearTime", "timeColor");

	//コロン
	m_colonTex.Load("Asset/Textures/UI/Text/colon.png");
	m_colonPos = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "colonPos");
	m_colonScale = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "colonScale");
	m_colonTexSize = JsonManager::Instance().GetParamVec2(_filePath, "ClearTime", "colonTexSize");
	m_colonColor = JsonManager::Instance().GetParamVec4(_filePath, "ClearTime", "colonColor");

	m_filePath = _filePath;
}

void ClearTime::DrawSprite()
{
	//描画の範囲
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
	if (m_drawFlg)
	{
		//時間
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.secPosR.x, m_time.secPosR.y,
			m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.secRectR, &m_time.color);

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.secPosL.x, m_time.secPosL.y,
			m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.secRectL, &m_time.color);

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex,m_time.minPosR.x, m_time.minPosR.y,
			m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.minRectR, &m_time.color);

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_time.minPosL.x, m_time.minPosL.y,
			m_time.texSize.x * m_time.scale.x, m_time.texSize.y * m_time.scale.y, &m_time.minRectL, &m_time.color);

		//コロン
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_colonTex, m_colonPos.x, m_colonPos.y,
			m_colonTexSize.x * m_colonScale.x, m_colonTexSize.y * m_colonScale.y, &m_colonRect, &m_colonColor);
	}
}

void ClearTime::Update()
{

}

void ClearTime::Restart()
{
	Init(m_filePath);
}
