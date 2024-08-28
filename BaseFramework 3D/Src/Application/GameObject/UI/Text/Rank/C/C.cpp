#include "C.h"
#include"../../../../../main.h"

void C::Init()
{
	UIBase::Init();
	m_pos = { -250,80 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/c.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 61,71 };
}

void C::Update()
{
}
