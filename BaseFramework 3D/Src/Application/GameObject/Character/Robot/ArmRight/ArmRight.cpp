#include "ArmRight.h"

void ArmRight::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Robot/Arm/armRight.gltf");
	m_pos = { -10,3,0 };
	m_color = { 1,1,1,1 };
}

void ArmRight::Update()
{
	if (m_flg)
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
