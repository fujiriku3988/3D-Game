#include "FPSCamera.h"
#include"../../../Scene/SceneManager.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();
	m_spCamera->SetProjectionMatrix(90);
	//Game
	{
		// 基準点(ターゲット)の目線
		//m_camPos = { 0, 6.0f, 8.0f };
		//m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);//ホワイトボードの位置（最初の定位置）
	}
	//GameDevelop
	{
		// 基準点(ターゲット)の目線
		m_camPos = { 0, 6.0f, 8.0f };
		//m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);//ホワイトボードの位置（最初の定位置）
	}
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}
	m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);

	// カメラの回転
	//UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mRotation * m_mLocalPos;

	CameraBase::Update();
}
