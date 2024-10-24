#include "Container.h"

void Container::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Structure/Container/Container2.gltf");
	m_pos = { 1.7f,0.0f,5.0f };
	m_scale = { 0.8f };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Container", m_modelWork, KdCollider::TypeEvent | KdCollider::TypeBump);
	m_objType = eContainer;
	m_prodType = eNoneCont;
}

void Container::Update()
{
	m_pos += m_dir * m_speed;
	//m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = m_scaleMat * m_transMat;
}

void Container::PostUpdate()
{
}
