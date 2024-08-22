#include "Body.h"

void Body::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Robot/Body/body.gltf");
	m_pos = {0,3,0};
	m_color = { 1,1,1,1 };
}

void Body::Update()
{
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = rot * trans;
}
