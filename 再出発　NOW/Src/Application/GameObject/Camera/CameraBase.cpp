#include "CameraBase.h"

void CameraBase::Init(const std::string _filePath)
{
}

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
	// ↓画面中央座標
	m_FixMousePos = JsonManager::Instance().GetParamPOINT("Asset/Data/Json/BaseFile/CameraBase.json", "CameraBase", "mousePos");
	//補正値
	m_crrValue = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/CameraBase.json", "CameraBase", "crrValue");
}

void CameraBase::Update()
{
	if (!m_spCamera) { return; }

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera) { return; }

	m_spCamera->SetToShader();
}

void CameraBase::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理(m_crrValueはただの補正値)
	m_DegAng.y += _mouseMove.x * m_crrValue;

}