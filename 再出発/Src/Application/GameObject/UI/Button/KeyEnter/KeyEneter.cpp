#include "KeyEnter.h"
#include"../../../../main.h"

void KeyEnter::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/enterKey.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "KeyEnter", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "KeyEnter", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "KeyEnter", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "KeyEnter", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "KeyEnter", "drawFlg");
}

void KeyEnter::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void KeyEnter::Update()
{

}
