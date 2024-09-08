#include "Chair.h"

void Chair::Init()
{
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Chair/Chair2.gltf");
	m_pos = { -2.0f,-1.5f,-1 };
}

void Chair::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(7);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));//大体0.5が25度くらい
	m_mWorld = scaleMat * rotMatY * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld);
}