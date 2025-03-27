#include "BgmTXT.h"
#include"../../../../../main.h"

#include "../../../../../Scene/SceneManager.h"
#include"../../../../../Fade/Fade.h"

void BgmTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/bgm.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "bgmTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "bgmTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "bgmTXT", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "bgmTXT", "texSizeHarf");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "bgmTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "bgmTXT", "drawFlg");
}

void BgmTXT::DrawSprite()
{
	if (m_drawFlg == true)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void BgmTXT::Update()
{
}
