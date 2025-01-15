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
	m_filePath = _filePath;
}

void KeyB::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
	}
}

void KeyB::Update()
{
	
}

void KeyB::Restart()
{
	Init(m_filePath);
}
