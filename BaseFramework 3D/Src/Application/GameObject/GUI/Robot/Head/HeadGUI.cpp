#include "HeadGUI.h"
#include"../../../../main.h"

void HeadGUI::Init()
{
	RobotGUIBase::Init();
	m_tex1.Load("Asset/Textures/UI/Robot/head1.png");
	m_tex2.Load("Asset/Textures/UI/Robot/head2.png");
	m_pos = { 500,260 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_texSize = { 50,50 };
}
