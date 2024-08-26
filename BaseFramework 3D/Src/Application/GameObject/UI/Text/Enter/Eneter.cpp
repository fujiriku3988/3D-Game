#include "Enter.h"
#include"../../../../Fade/Fade.h"
#include"../../../../Scene/SceneManager.h"

void Enter::Init()
{
	m_pos = { -250,-200 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/enter.png");
	m_color = { 1,1,1,1 };
	m_alpha = 1.0f;
	m_alphaMax = 360.0f;
	m_alphaMin = 0.3f;
	m_alphaSpeed = 2.0f;
}

void Enter::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		539 * m_scale.x, 72 * m_scale.y, nullptr, &m_color);
}

void Enter::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//キー制御
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			Fade::Instance().BootBlackFade(SceneManager::SceneType::Game);
		}
	}

	m_alphaSpeed += 2.0f;
	if (m_alphaSpeed >= m_alphaMax)
	{
		m_alphaSpeed -= m_alphaMax;
	}
	//360度が1radだから
	//m_alphaSpeedは1rad～-1radの値しかでないから0.35fをかけて
	//0.35f～-0.35fの幅で値を変える
	m_alpha = sin(DirectX::XMConvertToRadians(m_alphaSpeed)) * 0.35f + 0.65f;
	

	/*m_alpha -= m_alphaSpeed;

	if (m_alpha <= m_alphaMin) { m_alphaSpeed *= -1; }
	if (m_alpha > m_alphaMax) { m_alphaSpeed *= -1; }*/

}
