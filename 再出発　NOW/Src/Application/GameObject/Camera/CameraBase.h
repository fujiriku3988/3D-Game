#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase() {}
	virtual ~CameraBase()	override {}

	virtual void Init(const std::string _filePath);
	void Init()				override;
	void Update()			override;
	void PreDraw()			override;

	//追加
	void SetDegAngY(const float _degY) { m_DegAng.y = _degY; }
	void SetDegAngX(const float& _degX) { m_DegAng.x = _degX; }
	void SetCameraPos(Math::Vector3 _pos) { m_pos = _pos; }

	const std::shared_ptr<KdCamera>& GetCamera() const
	{
		return m_spCamera;
	}

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

	//追加
	Math::Vector3 m_pos = {};

	Math::Matrix m_mLocalPos = Math::Matrix::Identity;
	Math::Matrix m_mRotation = Math::Matrix::Identity;

	// カメラ回転用マウス座標の差分
	POINT m_FixMousePos{};

	//補正値
	float m_crrValue = {};//correctValue
};