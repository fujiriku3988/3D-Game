#include "LegRightGUI.h"
#include"../../../../main.h"

void LegRightGUI::Init()
{
	RobotGUIBase::Init();
	m_tex1.Load("Asset/Textures/GUI/Robot/leg1.png");
	m_tex2.Load("Asset/Textures/GUI/Robot/leg2.png");
	m_pos = { 480,145 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_texSize = { 16,50 };
}
