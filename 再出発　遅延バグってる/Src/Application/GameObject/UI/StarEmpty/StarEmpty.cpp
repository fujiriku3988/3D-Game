#include "StarEmpty.h"
#include"../../../main.h"

void StarEmpty::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/starEmpty.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "StarEmpty", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "StarEmpty", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "StarEmpty", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "StarEmpty", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "StarEmpty", "drawFlg");

	m_filePath = _filePath;
}

void StarEmpty::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void StarEmpty::Update()
{
	
}

void StarEmpty::Restart()
{
	Init(m_filePath);
}
