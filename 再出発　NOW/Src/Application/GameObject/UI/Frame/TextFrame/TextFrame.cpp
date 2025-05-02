#include "TextFrame.h"
#include"../../../../main.h"

void TextFrame::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Frame/textFrame.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "TextFrame", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "TextFrame", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "TextFrame", "drawFlg");
}

void TextFrame::DrawSprite()
{
	//描画
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void TextFrame::Update()
{
}
