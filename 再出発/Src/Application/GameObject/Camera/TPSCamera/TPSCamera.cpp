#include "TPSCamera.h"

void TPSCamera::Init()
{
	//親クラスの初期化呼び出し
	CameraBase::Init();

	m_spCamera->SetProjectionMatrix(90);

	//注視点
	m_camPos = { 0, 4.0f, -15.0f };
	SetDegAngX((20));
	//SetDegAngX(DirectX::XMConvertToRadians(90));
	
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

	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (m_flg == false)
		{
			m_move = !m_move;
		}
		m_flg = true;
	}
	else
	{
		m_flg = false;
	}
	//カメラの回転
	if (m_move) { UpdateRotateByMouse(); }
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;

	CameraBase::Update();
}
