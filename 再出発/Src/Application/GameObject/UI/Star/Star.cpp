#include "Star.h"
#include"../../../main.h"

void Star::Init(const std::string _filePath)
{
}

void Star::Init()
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/star1.png");
	m_pos = { 0,230 };
	//m_scale = { 0.3f };
	m_scale = { 2.5f };
	m_texSize = { 64,60 };
	m_alpha = 0.1f;
	m_color = { 1,1,1,m_alpha };
	m_drawFlg = true;

	m_tex1.Load("Asset/Textures/UI/Effect/firework.png");
	m_pos1 = { 0,200 };
	m_scale1 = { 1.0f };
	m_texSize1 = { 256,256 };
	m_color1 = { 1,1,1,1 };
	m_anim = {};
	m_rect1 = { (long)m_texSize1.x* (long)m_anim.x,(long)m_texSize1.y* (long)m_anim.y,(long)m_texSize1.x ,(long)m_texSize1.x };

	/*JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Star/Stage1/Star1.json", "Star1", "pos", m_pos);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Star/Stage1/Star1.json", "Star1", "scale", m_scale);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Star/Stage1/Star1.json", "Star1", "texSize", m_texSize);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/UI/Star/Stage1/Star1.json", "Star1", "color", m_color);
	JsonManager::Instance().AddParam<bool>("Asset/Data/Json/UI/Star/Stage1/Star1.json", "Star1", "drawFlg", m_drawFlg);*/
}

void Star::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	m_rect1 = { (long)m_texSize1.x * (long)m_anim.x,(long)m_texSize1.y * (long)m_anim.y,256 , 256 };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);

		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex1, m_pos1.x, m_pos1.y,
			m_texSize1.x * m_scale1.x, m_texSize1.y * m_scale1.y, &m_rect1, &m_color1);
	}
}

void Star::Update()
{
	/*if (a)
	{
		m_scale.x += 0.1f;
		m_scale.y += 0.1f;
	}*/

	/*if (m_scale.x >= 2.0f && m_scale.y >= 2.0f)
	{
		m_scale.x = 1.5f;
		m_scale.y = 1.5f;
		a = false;

		m_anim.x += 1;
		if (m_anim.x >= 6)
		{
			m_anim.y += 1;
			m_anim.x = 0;
		}
		if (m_anim.y > 5)
		{
			m_anim.x = 6;
		}
	}*/


	if (a)
	{
		m_scale.x -= 0.05f;
		m_scale.y -= 0.05f;
		m_alpha += 0.1f;
	}

	if (m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
	}

	if (m_scale.x <= 1.5f && m_scale.y <= 1.5f)
	{
		m_scale.x = 1.5f;
		m_scale.y = 1.5f;
		a = false;

		m_anim.x += 1;
		if (m_anim.x >= 6)
		{
			m_anim.y += 1;
			m_anim.x = 0;
		}
		if (m_anim.y > 5)
		{
			m_anim.x = 6;
		}
	}
	

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			m_anim.x = j;
		}
		m_anim.y = i;
	}*/
}
