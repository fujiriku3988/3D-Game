#include "StarEmpty.h"
#include"../../../main.h"

void StarEmpty::Init(const std::string _filePath)
{
}

void StarEmpty::Init()
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/starEmpty.png");
	m_pos = { 0,230 };
	m_scale = { 1.5f };
	m_texSize = { 192,60 };
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
}

void StarEmpty::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void StarEmpty::Update()
{
	
}
