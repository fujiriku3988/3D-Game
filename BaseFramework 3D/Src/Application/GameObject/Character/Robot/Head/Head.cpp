#include "Head.h"

void Head::Init()
{
	CharacterBase::Init();
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Robot/Head/head1.gltf");
	m_pos = {0,13,0};
	m_color = { 1,1,1,1 };
}

void Head::Update()
{
	if (m_moveFlg)
	{
		m_pos.y -= 1;
	}
	if (m_pos.y <= 3)
	{
		m_pos.y = 3;
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = rot * trans;

}
