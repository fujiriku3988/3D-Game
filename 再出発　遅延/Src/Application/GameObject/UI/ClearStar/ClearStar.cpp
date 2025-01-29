#include "ClearStar.h"
#include"../../../main.h"

void ClearStar::Init(const std::string _filePath)
{
	UIBase::Init();

	//スター
	m_starFilePath = JsonManager::Instance().GetParam <std::string>(_filePath, "ClearStar", "starFP");
	m_starTex.Load(m_starFilePath);
	m_starPos = JsonManager::Instance().GetParamVec2(_filePath, "ClearStar", "starPos");
	m_starScale = JsonManager::Instance().GetParamVec2(_filePath, "ClearStar", "starScale");
	m_starTexSize = JsonManager::Instance().GetParamVec2(_filePath, "ClearStar", "starTexSize");
	m_starColor = JsonManager::Instance().GetParamVec4(_filePath, "ClearStar", "starColor");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "ClearStar", "drawFlg");

	m_filePath = _filePath;
}

void ClearStar::DrawSprite()
{
	if (m_drawFlg)
	{
		//スター
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_starTex, m_starPos.x, m_starPos.y,
			m_starTexSize.x * m_starScale.x,m_starTexSize.y * m_starScale.y, nullptr, &m_starColor);
	}
}

void ClearStar::Update()
{

}

void ClearStar::Restart()
{
	Init(m_filePath);
}
