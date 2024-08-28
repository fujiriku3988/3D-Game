#include "A.h"
#include"../../../../../main.h"

void A::Init()
{
	UIBase::Init();
	m_pos = { -250,80 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/a.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 65,71 };
}

void A::Update()
{
}
