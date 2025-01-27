#include "StageClearTXT.h"
#include"../../../../main.h"

void StageClearTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/StageClear.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "StageClearTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "StageClearTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "StageClearTXT", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "StageClearTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "StageClearTXT", "drawFlg");

	m_filePath = _filePath;
}

void StageClearTXT::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void StageClearTXT::Update()
{
	
}

void StageClearTXT::Restart()
{
	Init(m_filePath);
}
