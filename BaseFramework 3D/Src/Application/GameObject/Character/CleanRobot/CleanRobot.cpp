#include "CleanRobot.h"

void CleanRobot::Init()
{
	CharacterBase::Init();
	m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData("Asset/Models/CleanRobot/cleanRobot.gltf");
	m_pos = {};
	m_color = { 1,1,1,1 };
}

void CleanRobot::Update()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}
