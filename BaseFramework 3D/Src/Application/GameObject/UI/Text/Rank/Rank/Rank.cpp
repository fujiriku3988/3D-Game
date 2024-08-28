#include "Rank.h"
#include"../../../../../main.h"

void Rank::Init()
{
	UIBase::Init();
	m_pos = { -250,230 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/rank.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 214,71 };
}

void Rank::Update()
{
}
