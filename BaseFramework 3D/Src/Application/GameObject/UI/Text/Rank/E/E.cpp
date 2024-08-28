#include "E.h"
#include"../../../../../main.h"

void E::Init()
{
	UIBase::Init();
	m_pos = { -250,80 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/e.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 62,70 };
}

void E::Update()
{
}
