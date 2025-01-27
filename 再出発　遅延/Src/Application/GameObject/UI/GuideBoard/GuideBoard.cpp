#include "GuideBoard.h"

void GuideBoard::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/GuideBoard/guide.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "GuideBoard", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "GuideBoard", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "GuideBoard", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "GuideBoard", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "GuideBoard", "drawFlg");
	m_filePath = _filePath;
}

void GuideBoard::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void GuideBoard::Update()
{
}

void GuideBoard::Restart()
{
	Init(m_filePath);
}
