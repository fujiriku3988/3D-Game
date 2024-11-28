#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase() {}
	virtual ~CameraBase()	override {}

	void Init()				override;
	void Update()			override;
	void PreDraw()			override;

	//追加
	void SetTarget(const std::shared_ptr<KdGameObject>& target);
	void SetDegAngY(float _degY) { m_DegAng.y = _degY; }
	void SetDegAngX(float _degX) { m_DegAng.x = _degX; }
	void SetCameraPos(Math::Vector3 _pos) { m_camPos = _pos; }
	bool GetDegAngYFlg() { return m_degFlgY; }
	bool GetDegAngXFlg() { return m_degFlgX; }
	bool GetCamPosFlg() { return m_camFlg; }

	// 「絶対変更しません！見るだけ！」な書き方
	const std::shared_ptr<KdCamera>& GetCamera() const
	{
		return m_spCamera;
	}

	// 「中身弄るかもね」な書き方
	std::shared_ptr<KdCamera> WorkCamera() const
	{
		return m_spCamera;
	}

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_DegAng.y));
	}

	const Math::Vector3 GetDegAng() { return m_DegAng; }
private:
	// カメラ回転用角度
	Math::Vector3				m_DegAng = Math::Vector3::Zero;

protected:
	void UpdateRotateByMouse();

	std::shared_ptr<KdCamera>	m_spCamera = nullptr;
	std::weak_ptr<KdGameObject>	m_wpTarget;

	//追加
	Math::Vector3 m_camPos = {};
	bool m_degFlgX = false;//回転終わったか
	bool m_degFlgY = false;//回転終わったか
	bool m_camFlg = false;//カメラの移動終わったか

	Math::Matrix m_mLocalPos = Math::Matrix::Identity;
	Math::Matrix m_mRotation = Math::Matrix::Identity;

	// カメラ回転用マウス座標の差分
	POINT m_FixMousePos{};
};