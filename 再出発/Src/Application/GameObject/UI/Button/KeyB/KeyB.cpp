#include "KeyB.h"
#include"../../../../main.h"

void KeyB::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/bKey.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "KeyB", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "KeyB", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "KeyB", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "KeyB", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "KeyB", "drawFlg");
}

void KeyB::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void KeyB::Update()
{
	
}
