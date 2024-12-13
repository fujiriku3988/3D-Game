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
private:
	//消す
	bool m_flg = false;
	bool m_move = true;
	bool m_rotFlg = true;
};