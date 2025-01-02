#pragma once
#include "../CameraBase.h"

class TPSCamera : public CameraBase
{
public:
	TPSCamera() {}
	~TPSCamera()override {}

	void Init()override;
	void Update()override;

	void RotateMouseOFF() { m_rotFlg = false; }
	void Restart()override;

	// 線形補間関数 (lerp)
	Math::Vector3 Lerp(const Math::Vector3& _start, const Math::Vector3& _end, float _time)
	{
		return _start + _time * (_end - _start);
	}

	void updateCamera(Math::Vector3& _cameraPosition, const Math::Vector3& _targetPosition, float _deltaTime)
	{
		// 補間係数（追従速度）
		m_time = m_followSpeed * _deltaTime;

		// カメラ位置をターゲット（キャラクターの上）に向けて補間
		_cameraPosition = Lerp(_cameraPosition, _targetPosition, m_time);
	}

	float GetDeltaTime()
	{
		static auto lastTime = std::chrono::steady_clock::now();
		auto currentTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		return deltaTime;
	}

private:
	//消す
	bool m_flg = false;
	bool m_move = true;
	bool m_rotFlg = true;

	// カメラの視点オフセット用
	Math::Vector3 cameraOffset;
	// 補間係数（追従速度）
	float m_followSpeed;  // 追従の速さ
	float m_time;
};