#include "StageFrame.h"
#include"../../../../main.h"

void StageFrame::Init(const std::string _filePath)
{
	m_tex.Load("Asset/Textures/UI/Frame/stageFrame.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "StageFrame", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "StageFrame", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "StageFrame", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "StageFrame", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "StageFrame", "drawFlg");
}

void StageFrame::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void StageFrame::Update()
{
}
