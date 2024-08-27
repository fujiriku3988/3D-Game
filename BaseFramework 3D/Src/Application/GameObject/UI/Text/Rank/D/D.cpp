#include "D.h"
#include"../../../../../main.h"

void D::Init()
{
	UIBase::Init();
	m_pos = { -250,-50 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/d.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 65,72 };
}

void D::Update()
{
}
