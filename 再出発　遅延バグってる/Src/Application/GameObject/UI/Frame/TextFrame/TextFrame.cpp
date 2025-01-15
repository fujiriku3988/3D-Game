#include "TextFrame.h"
#include"../../../../main.h"

void TextFrame::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/textFrame.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "TextFrame", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "TextFrame", "drawFlg");
}

void TextFrame::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void TextFrame::Update()
{
}
