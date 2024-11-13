#include "Conver.h"

void Conver::Init()
{
	ObjectBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/Object/Structure/Conver/Conver1.gltf");
	//m_modelWork->SetModelData("Asset/Models/Object/Structure/Conver/Water/Water.gltf");
	m_pos = { -5,0,5 };
	m_adjustHeight = -0.0f;
	m_gravity = 0.0f;
	m_gravityPow = 0.004f;
	m_color = { 1,1,1,1 };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Conver", m_modelWork, KdCollider::TypeBump);
	m_objType = eConver;
}

void Conver::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.SetUVOffset(m_UVOffSet);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, m_mWorld, m_color);
}

void Conver::Update()
{
	m_UVOffSet.x += 0.0001f;
	//m_UVOffSet.y += 0.00001f;
	m_pos += m_dir * m_speed;
	//m_gravity += m_gravityPow;
	m_pos.y += -m_gravity;
	//スピード計算
	m_speed -= 0.1f;

	if (m_speed <= 0) { m_speed = 0; }
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;
}

void Conver::PostUpdate()
{
}
