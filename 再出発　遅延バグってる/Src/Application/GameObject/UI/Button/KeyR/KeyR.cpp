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
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
	}
}

void KeyR::Update()
{
}

void KeyR::Restart()
{
	Init(m_filePath);
}
