#include "TitleTXT.h"
#include"../../../../main.h"

void TitleTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/title.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "TitleTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "TitleTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "TitleTXT", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "TitleTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "TitleTXT", "drawFlg");
}

void TitleTXT::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void TitleTXT::Update()
{
	
}
