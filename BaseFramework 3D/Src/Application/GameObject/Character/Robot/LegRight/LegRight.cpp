﻿#include "LegRight.h"

void LegRight::Init()
{
	CharacterBase::Init();
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Robot/Leg/legRight.gltf");
	m_pos = { -15,3,0 };
	m_color = { 1,1,1,1 };
}

void LegRight::Update()
{
	if (m_moveFlg)
	{
		m_pos.x += 1;
	}
	if (m_pos.x >= 0)
	{
		m_pos.x = 0;
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = rot * trans;
}
