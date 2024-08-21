#include "Chair.h"

void Chair::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Chair/Chair2.gltf");
	m_pos = { -2.0f,-1.5f,-1 };
}

void Chair::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(7);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(3.1);//大体0.5が25度くらい
	m_mWorld = scaleMat * rotMatY * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}