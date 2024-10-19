#include "CardBoard.h"

void CardBoard::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Structure/CardBoard/CardBoard.gltf");
	m_pos = { 5.0f,1.0f,0.0f };
	m_scale = { 2.0f };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CardBoard", m_modelWork, KdCollider::TypeEvent);
	m_objType = eCardBoard;
}

void CardBoard::Update()
{
	m_pos += m_dir * m_speed;
	m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	CollisionGround(m_pos, Math::Vector3::Down, KdCollider::TypeGround, m_adjustHeight);

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = m_scaleMat * m_transMat;
}

void CardBoard::PostUpdate()
{
	
}
