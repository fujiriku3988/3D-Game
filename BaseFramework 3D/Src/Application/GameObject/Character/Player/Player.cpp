#include "Player.h"

void Player::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tank/Tank.gltf");
	m_pos = {};
	m_color = { 1,1,1,1 };
}

void Player::Update()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}
