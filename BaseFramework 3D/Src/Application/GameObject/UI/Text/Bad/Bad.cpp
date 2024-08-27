#include "Bad.h"
#include"../../../../main.h"

void Bad::Init()
{
	UIBase::Init();
	m_pos = { 300,0 };
	m_scale = { 0.3f };
	m_tex.Load("Asset/Textures/UI/Text/bad.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_texSize = { 134,80 };
}

void Bad::Update()
{
	m_scale.x += 0.1f;
	m_scale.y += 0.1f;
	if (m_scale.x >= 2.0f && m_scale.y >= 2.0f)
	{
		m_scale = { 2 };
		m_time--;
	}
	if (m_time <= 0)
	{
		m_isExpired = true;
	}
}
