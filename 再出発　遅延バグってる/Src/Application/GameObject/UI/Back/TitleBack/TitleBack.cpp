#include "TitleBack.h"
#include"../../../../main.h"

void TitleBack::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Back/tback.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "TitleBack", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "TitleBack", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "TitleBack", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "TitleBack", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "TitleBack", "drawFlg");
}

void TitleBack::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
	}
}

void TitleBack::Update()
{
}
