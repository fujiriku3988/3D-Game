#include "SeTXT.h"
#include"../../../../../main.h"

#include "../../../../../Scene/SceneManager.h"
#include"../../../../../Fade/Fade.h"

void SeTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/se.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "seTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "seTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "seTXT", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "seTXT", "texSizeHarf");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "seTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "seTXT", "drawFlg");
}

void SeTXT::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void SeTXT::Update()
{
	
}
