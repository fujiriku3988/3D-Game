#include "S.h"
#include"../../../../../main.h"

void S::Init()
{
	UIBase::Init();
	m_pos = { -250,80 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/s.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 55,74 };
}

void S::Update()
{
}
