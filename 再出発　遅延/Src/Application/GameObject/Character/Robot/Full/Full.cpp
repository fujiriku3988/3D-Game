#include "Full.h"

void Full::Init()
{
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Robot/Full/Full.gltf");
	m_pos = { 0,3,0 };
	m_color = { 1,1,1,1 };
	m_rot.x = 90;
}

void Full::Update()
{
	m_rot.x += 1.0f;
	if (m_rot.x >= 360)
	{
		m_rot.x -= 360;
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.x));
	m_mWorld = rot * trans;
}
