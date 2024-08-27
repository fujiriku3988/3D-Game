#include "LegLeftGUI.h"
#include"../../../../main.h"

void LegLeftGUI::Init()
{
	RobotGUIBase::Init();
	m_tex1.Load("Asset/Textures/UI/Robot/leg1.png");
	m_tex2.Load("Asset/Textures/UI/Robot/leg2.png");
	m_pos = { 520,145 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_texSize = { 16,50 };
}