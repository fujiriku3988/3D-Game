#include "StageFrame.h"
#include"../../../../main.h"

void StageFrame::Init(const std::string _filePath)
{
	m_tex.Load("Asset/Textures/UI/Result/stageFrame.png");
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
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (float)m_pos.x, (float)m_pos.y,
			(float)m_texSize.x * (float)m_scale.x, (float)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void StageFrame::Update()
{
}
