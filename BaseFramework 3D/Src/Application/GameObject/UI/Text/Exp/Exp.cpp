#include "Exp.h"
#include"../../../../main.h"

void Exp::Init()
{
	UIBase::Init();
	m_pos = { -450,-100 };
	m_scale = { 0.5f };
	m_tex.Load("Asset/Textures/UI/Text/exp.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 153,86 };
}

void Exp::Update()
{
}
