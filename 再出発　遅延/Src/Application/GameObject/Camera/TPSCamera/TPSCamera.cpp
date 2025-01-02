#include "TPSCamera.h"

void TPSCamera::Init()
{
	//親クラスの初期化呼び出し
	CameraBase::Init();
	m_rotFlg = true;

	m_spCamera->SetProjectionMatrix(90);

	//注視点
	m_camPos = { 0, 4.0f, -15.0f };
	cameraOffset= { 0, 4.0f, -15.0f };
	SetDegAngX((20));
	
	m_mLocalPos = Math::Matrix::CreateTranslation(m_camPos);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::Update()
{
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!m_flg)
		{
			m_rotFlg = !m_rotFlg;
		}
		m_flg = true;
	}
	else
	{
		m_flg = false;
	}

	// ターゲット（プレイヤー）の有効性を確認
	const std::shared_ptr<const KdGameObject> target = m_wpTarget.lock();
	if (!target)
	{
		// ターゲットが存在しない場合はデフォルトの処理
		return;
	}

	// プレイヤーの位置を取得
	Math::Vector3 playerPos = target->GetPos();

	// カメラの目標位置を計算
	Math::Vector3 relativeCameraPos = cameraOffset; // カメラの相対位置
	if (m_rotFlg)
	{
		// マウスによる回転処理
		UpdateRotateByMouse();
	}

	// 回転行列を生成して相対位置を回転
	Math::Matrix rotationMatrix = GetRotationMatrix();
	Math::Vector3 rotatedOffset = Math::Vector3::Transform(relativeCameraPos, rotationMatrix);

	// 回転後の目標位置を計算
	Math::Vector3 targetCameraPos = playerPos + rotatedOffset;

	// 遅延追従の計算
	float followSpeed = 5.0f; // カメラの追従速度
	float deltaTime = GetDeltaTime(); // フレームごとの経過時間
	m_camPos = Math::Vector3::Lerp(m_camPos, targetCameraPos, followSpeed * deltaTime);

	// カメラのワールド行列を計算
	Math::Matrix translationMatrix = Math::Matrix::CreateTranslation(m_camPos);
	m_mWorld = rotationMatrix * translationMatrix;

	// カメラベースクラスの更新を呼び出す
	CameraBase::Update();
}

void TPSCamera::Restart()
{
	Init();
}
