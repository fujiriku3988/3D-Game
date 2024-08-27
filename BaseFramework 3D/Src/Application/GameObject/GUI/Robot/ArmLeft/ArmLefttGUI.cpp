﻿#include "ArmLeftGUI.h"
#include"../../../../main.h"

void ArmLeftGUI::Init()
{
	RobotGUIBase::Init();
	m_tex1.Load("Asset/Textures/UI/Robot/arm1.png");
	m_tex2.Load("Asset/Textures/UI/Robot/arm2.png");
	m_pos = { 550,210 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_texSize = { 50,26 };
}
