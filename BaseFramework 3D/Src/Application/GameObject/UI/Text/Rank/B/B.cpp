#include "B.h"
#include"../../../../../main.h"

void B::Init()
{
	UIBase::Init();
	m_pos = { -250,-50 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/b.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 62,70 };
}

void B::Update()
{
}
