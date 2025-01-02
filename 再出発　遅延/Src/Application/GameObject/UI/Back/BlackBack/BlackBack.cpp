#include "BlackBack.h"

void BlackBack::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/black.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "BlackBack", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "BlackBack", "drawFlg");
	m_filePath = _filePath;
}

void BlackBack::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void BlackBack::Update()
{
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_drawFlg = true;
	}

	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_drawFlg = false;
	}
}

void BlackBack::Restart()
{
	Init(m_filePath);
}
