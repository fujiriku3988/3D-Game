#pragma once
#include "../CameraBase.h"
class Player;

class TPSCamera : public CameraBase
{
public:
	TPSCamera() {}
	~TPSCamera()override {}

	void Init(const std::string _filePath)override;
	void Update()override;

	void RotateMouseOFF() { m_rotFlg = false; }
	void Restart()override;

	//ポインターセット
	void SetTarget(const std::shared_ptr<Player>& _target);

	//線形補間関数 (lerp)
	Math::Vector3 Lerp(const Math::Vector3& _start, const Math::Vector3& _end, float _time)
	{
		return _start + _time * (_end - _start);
	}
	//デルタタイム取得
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

	std::weak_ptr<Player>	m_wpTarget;
	//カメラの視点オフセット用
	Math::Vector3 m_offSet;
	//補間係数（追従速度）
	//追従の速さ
	float m_followSpeed = {};
	//視野角
	float m_viewAng = {};
	//アングル
	Math::Vector2 m_angle = {};
};