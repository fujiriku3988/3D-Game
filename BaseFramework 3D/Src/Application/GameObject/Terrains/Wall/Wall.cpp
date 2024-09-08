#include "Wall.h"

void Wall::Init()
{
	m_modelData = std::make_shared<KdModelData>();
	m_modelData->Load("Asset/Models/Wall/Wall2.gltf");
	m_pos = {0,0,0};
}

void Wall::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, m_mWorld);
}

void Wall::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));//大体0.5が25度くらい
	m_mWorld = scaleMat * rotMatY * transMat;
}
