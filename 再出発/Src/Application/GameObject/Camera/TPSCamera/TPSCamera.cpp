﻿#include "TPSCamera.h"

void TPSCamera::Init()
{
	//親クラスの初期化呼び出し
	CameraBase::Init();

	m_spCamera->SetProjectionMatrix(90);

	//注視点
	m_camPos = { 0, 4.0f, -12.0f };
	SetDegAngX(DirectX::XMConvertToRadians(120));
	
	m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);//ホワイトボードの位置（最初の定位置）

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::Update()
{
	//ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;

	CameraBase::Update();
}
