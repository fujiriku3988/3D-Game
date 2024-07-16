#include "AssetManager.h"

void AssetManager::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_poly = std::make_shared<KdSquarePolygon>();
}

void AssetManager::LoadAsset(const std::string name, const std::string filepass)
{
	m_model->SetModelData(filepass);
	m_asset[name] = m_model;
}
