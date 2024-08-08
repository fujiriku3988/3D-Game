#include "Boad.h"
#include"../../../main.h"
#include"../../../GameObject/Camera/CameraBase.h"
//#include"../../../GameObject/Camera/TPSCamera/TPSCamera.h"

void Boad::Init()
{
	m_Spos = { 400,0 };
	m_tex.Load("Asset/Textures/UI/boad.png");
	m_color = { 1,1,1,1 };
	m_flg = true;
	m_rotFlg = false;
}

void Boad::DrawSprite()
{
	if (m_flg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_Spos.x, m_Spos.y, 384, 128, nullptr, &m_color);
}

void Boad::Update()
{
	POINT nowPos;
	GetCursorPos(&nowPos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	POINT nowLength;

	nowLength.x = (nowPos.x - 640) - m_Spos.x;
	nowLength.y = (nowPos.y - 360) - m_Spos.y;

	//if (nowLength.x >= m_Spos.x-180 && nowLength.x <= m_Spos.x+200)
	std::shared_ptr<CameraBase>spCamera = m_wpCamera.lock();
	if (spCamera->GetDegAng().y == 45) { m_flg = false; }
	if (nowLength.y >= m_Spos.y - 40 && nowLength.y <= m_Spos.y + 90
		&& nowLength.x >= m_Spos.x - 580 && nowLength.x <= m_Spos.x - 200)
	{
		m_color = { 1,1,1,0.2f };
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_rotFlg = true;
			m_flg = false;
		}
		if (m_rotFlg) { spCamera->SetDegAng(Math::Vector3{ 0,45,0 }); }
	}
	else
	{
		m_color = { 1,1,1,1 };
		//m_flg = false;
	}
}
