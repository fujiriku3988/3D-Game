#include "StageSelectTXT.h"
#include"../../../../main.h"

void StageSelectTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/StaeSelect.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "StageSelectTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "StageSelectTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "StageSelectTXT", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "StageSelectTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "StageSelectTXT", "drawFlg");
}

void StageSelectTXT::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
	}
}

void StageSelectTXT::Update()
{
	
}
