#include "CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
	// ↓画面中央座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
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

void CameraBase::SetTarget(const std::shared_ptr<KdGameObject>& target)
{
	if (!target) { return; }

	m_wpTarget = target;
}

void CameraBase::SetDegAngY(float _degY)
{
	float DegMaxY = _degY;
	//指定した値がマイナスかプラスか
	//マイナスならマイナス方向に
	//プラスならプラス方向に
	if (DegMaxY < 0)
	{
		m_DegAng.y -= 1.0f;
		if (m_DegAng.y <= DegMaxY)
		{
			m_DegAng.y = DegMaxY;
		}
	}
	if (DegMaxY > 0)
	{
		m_DegAng.y += 1.0f;
		if (m_DegAng.y >= DegMaxY)
		{
			m_DegAng.y = DegMaxY;
		}
	}
	if (m_DegAng.y == DegMaxY)
	{
		m_degFlgY = true;
	}
	else
	{
		m_degFlgY = false;
	}
}

void CameraBase::SetDegAngX(float _degX)
{
	float DegMaxX = _degX;
	//指定した値がマイナスかプラスか
	//マイナスならマイナス方向に
	//プラスならプラス方向に
	if (DegMaxX < 0)
	{
		m_DegAng.x -= 1.0f;
		if (m_DegAng.x <= DegMaxX)
		{
			m_DegAng.x = DegMaxX;
		}
	}
	if (DegMaxX > 0)
	{
		m_DegAng.x += 1.0f;
		if (m_DegAng.x >= DegMaxX)
		{
			m_DegAng.x = DegMaxX;
		}
	}
	if (m_DegAng.x == DegMaxX)
	{
		m_degFlgX = true;
	}
	else
	{
		m_degFlgX = false;
	}
	//使うかも？
	//m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}

void CameraBase::SetCamPos(Math::Vector3 _pos)
{
	Math::Vector3 maxPos = _pos;
	//m_camPos = { 0, 10.0f, 0.0f };
	//m_camPos = { 0, 10.0f, 0.0f };

	//カメラを下に回転させる場合
	if (maxPos.y > 0)
	{
		m_camPos.y += 0.1f;
		if (m_camPos.y >= maxPos.y)
		{
			m_camPos.y = maxPos.y;
		}
	}
	if (maxPos.z < 0)
	{
		m_camPos.z -= 0.1f;
		if (m_camPos.z <= maxPos.z)
		{
			m_camPos.z = maxPos.z;
		}
	}
	//カメラを上に回転させる場合
	if (maxPos.y < 0)
	{
		m_camPos.y -= 0.1f;
		if (m_camPos.y <= maxPos.y)
		{
			m_camPos.y = maxPos.y;
		}
	}
	if (maxPos.z > 0)
	{
		m_camPos.z += 0.1f;
		if (m_camPos.z >= maxPos.z)
		{
			m_camPos.z = maxPos.z;
		}
	}
	if (m_camPos.y == maxPos.y && m_camPos.z == maxPos.z)
	{
		m_camFlg = true;
	}
	else
	{
		m_camFlg = false;
	}
	m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);
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

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
}