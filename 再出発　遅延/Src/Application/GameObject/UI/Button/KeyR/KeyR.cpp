#include "KeyR.h"
#include"../../../../main.h"

void KeyR::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/rKey.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "KeyR", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "KeyR", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "KeyR", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "KeyR", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "KeyR", "drawFlg");
	m_filePath = _filePath;
}

void KeyR::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void KeyR::Update()
{
}

void KeyR::Restart()
{
	Init(m_filePath);
}
