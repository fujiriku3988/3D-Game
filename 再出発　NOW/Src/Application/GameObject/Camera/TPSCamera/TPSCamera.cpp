#include "TPSCamera.h"
#include "../../../GameObject/Character/Player/Player.h"

void TPSCamera::Init(const std::string _filePath)
{
	//親クラスの初期化呼び出し
	CameraBase::Init();
	m_rotFlg = true;
	//注視点
	m_pos = JsonManager::Instance().GetParamVec3(_filePath, "TPSCamera", "pos");
	m_offSet = JsonManager::Instance().GetParamVec3(_filePath, "TPSCamera", "offset");
	//カメラのアングル
	m_angle = JsonManager::Instance().GetParamVec2(_filePath, "TPSCamera", "angle");
	//カメラの視野角
	m_viewAng = JsonManager::Instance().GetParam<float>(_filePath, "TPSCamera", "viewAng");
	//カメラの追従速度
	m_followSpeed = JsonManager::Instance().GetParam<float>(_filePath, "TPSCamera", "followSpd");
	//ファイルパス記憶
	m_filePath = _filePath;

	m_spCamera->SetProjectionMatrix(m_viewAng);
	SetDegAngX((m_angle.x));
	//マウスカーソルの初期値
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);
}

void TPSCamera::Update()
{
	ShowCursor(true);
	if(GetAsyncKeyState('1') & 0x8000)
	{
		if (a == false)
		{
			m_rotFlg = !m_rotFlg;
			a = true;
		}
	}
	else
	{
		a = false;
	}

	// ターゲット（プレイヤー）の有効性を確認
	const std::shared_ptr<Player> target = m_wpTarget.lock();
	if (!target)
	{
		// ターゲットが存在しない場合はデフォルトの処理
		return;
	}

	//プレイヤーの位置を取得
	Math::Vector3 playerPos = target->GetPos();

	// カメラの目標位置を計算
	Math::Vector3 relativeCameraPos = m_offSet; // カメラの相対位置
	if (m_rotFlg)
	{
		//マウスによる回転処理
		UpdateRotateByMouse();
	}

	//回転行列を生成して相対位置を回転
	Math::Matrix rotationMatrix = GetRotationMatrix();
	Math::Vector3 rotatedOffset = Math::Vector3::Transform(relativeCameraPos, rotationMatrix);

	//回転後の目標位置を計算
	Math::Vector3 targetCameraPos = playerPos + rotatedOffset;

	//遅延追従の計算
	float deltaTime = GetDeltaTime();
	m_pos = Math::Vector3::Lerp(m_pos, targetCameraPos, m_followSpeed * deltaTime);

	//カメラのワールド行列を計算
	Math::Matrix translationMatrix = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotationMatrix * translationMatrix;

	//カメラベースクラスの更新を呼び出す
	CameraBase::Update();
}

void TPSCamera::Restart()
{
	Init(m_filePath);
}

void TPSCamera::SetTarget(const std::shared_ptr<Player>& _target)
{
	if (!_target) { return; }

	m_wpTarget = _target;
}
