#include "Enter.h"
#include"../../../../Fade/Fade.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../GUI/Bar/ExpBar/ExpBar.h"

void Enter::Init()
{
	UIBase::Init();
	m_pos = { -250,-200 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/enter.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 404,70 };
	m_alpha = 1.0f;
	m_alphaMax = 360.0f;
	m_alphaMin = 0.3f;
	m_alphaSpeed = 2.0f;
}

void Enter::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
}

void Enter::Update()
{
	std::shared_ptr<ExpBar>spExpBar = m_wpExpBar.lock();
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//キー制御
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			spExpBar->WriteFlgOff();
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

}