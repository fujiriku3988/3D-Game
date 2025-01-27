#include "UIBack.h"
#include"../../../../main.h"

void UIBack::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Back/uiBack.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "UIBack", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "UIBack", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "UIBack", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "UIBack", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "UIBack", "drawFlg");
}

void UIBack::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void UIBack::Update()
{
}
