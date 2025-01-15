#include "smoke.h"
#include"../../../main.h"

#include"../../Camera/CameraBase.h"
#include"../../Camera/TPSCamera/TPSCamera.h"

void smoke::Init(const std::string _filePath)
{
	EffectBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Effect/smoke.png");
	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "Smoke", "pos");
	m_scale = JsonManager::Instance().GetParamVec3(_filePath, "Smoke", "scale");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Smoke", "color");
	m_split = JsonManager::Instance().GetParamVec2(_filePath, "Smoke", "split");
	m_uvRect = JsonManager::Instance().GetParam<int>(_filePath, "Smoke", "uvRect");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Smoke", "drawFlg");
	m_anime.count = JsonManager::Instance().GetParam<int>(_filePath, "Smoke", "animCnt");
	m_anime.speed = JsonManager::Instance().GetParam<float>(_filePath, "Smoke", "animSpd");
	m_anime.MAX = JsonManager::Instance().GetParam<int>(_filePath, "Smoke", "animMAX");

	m_poly->SetSplit((int)m_split.x,(int)m_split.y);
	m_poly->SetUVRect(m_uvRect);

	m_filePath = _filePath;
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
