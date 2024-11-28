#include "BlueBack.h"

void BlueBack::Init(const std::string _string)
{
}

void BlueBack::Init()
{
	UIBase::Init();
	m_pos = { 0,0 };
	m_scale = { 4.0f,4.0f };
	m_tex.Load("Asset/Textures/UI/Result/back.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_drawFlg = true;
	m_texSize = { 64,64 };
}

void BlueBack::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void BlueBack::Update()
{
	//α値変更
	//m_alpha += m_speed;
	if (m_alpha < m_alphaMIN)
	{
		//m_speed *= -1;
	}
	if (m_alpha > m_alphaMAX)
	{
		//m_speed *= -1;
	}
}
