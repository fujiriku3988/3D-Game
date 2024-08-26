#include "LegLeft.h"

void LegLeft::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Robot/Leg/legLeft.gltf");
	m_pos = { 15,3,0 };
	//m_pos = { 0,3,0 };
	m_color = { 1,1,1,1 };
}

void LegLeft::Update()
{
	if (m_flg)
	{
		m_pos.x -= 1;
	}
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = rot * trans;
}
