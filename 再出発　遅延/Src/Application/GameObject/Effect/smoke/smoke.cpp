#include "smoke.h"
#include"../../../main.h"

#include"../../Camera/CameraBase.h"
#include"../../Camera/TPSCamera/TPSCamera.h"

void smoke::Init()
{
	EffectBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Effect/smoke.png");
	m_pos = {0,0};
	m_scale = {1.0f};
	m_color = { 0.8,0.8,0.8,1 };
	m_poly->SetSplit(7, 1);
	m_poly->SetUVRect(6);
	m_anime.count = 0;
	m_anime.speed = 0.2f;
	m_anime.MAX = 7;
}

void smoke::Init(const std::string _filePath)
{
	/*EffectBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/star1.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Star", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Star", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Star", "texSize");
	m_alpha = JsonManager::Instance().GetParam<float>(_filePath, "Star", "alpha");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Star", "drawFlg");

	m_filePath = _filePath;*/
}

void smoke::Update()
{
	m_anime.count += m_anime.speed;
	if (m_anime.count > m_anime.MAX)
	{
		m_isExpired = true;
	}
	m_poly->SetUVRect((int)m_anime.count);

	m_scaleMat = Math::Matrix::CreateScale(m_scale);
	m_transMat = Math::Matrix::CreateTranslation(m_pos);

	std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	Math::Matrix cameraMat = spCamera->GetMatrix();
	m_transMat.Backward(cameraMat.Backward());
	m_transMat.Up(cameraMat.Up());
	m_transMat.Right(cameraMat.Right());

	m_mWorld = m_scaleMat * m_transMat;
}

void smoke::Restart()
{
	Init(m_filePath);
}
