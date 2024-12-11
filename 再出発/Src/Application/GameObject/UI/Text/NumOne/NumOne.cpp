﻿#include "NumOne.h"
#include"../../../../main.h"

#include "../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void NumOne::Init()
{
	UIBase::Init();
	m_pos = { -300,0 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Text/one.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_drawFlg = true;
	m_texSize = { 64.0f,64.0f };

	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Text/NumOne.json", "NumOne", "pos", m_pos);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Text/NumOne.json", "NumOne", "scale", m_scale);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Text/NumOne.json", "NumOne", "texSize", m_texSize);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/UI/Text/NumOne.json", "NumOne", "color", m_color);
	JsonManager::Instance().AddParam<bool>("Asset/Data/Json/UI/Text/NumOne.json", "NumOne", "drawFlg", m_drawFlg);
}

void NumOne::Init(const std::string _filePath)
{
	m_tex.Load("Asset/Textures/UI/Text/one.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "NumOne", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "NumOne", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "NumOne", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "NumOne", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "NumOne", "drawFlg");
}

void NumOne::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(float)m_texSize.x * (float)m_scale.x, (float)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void NumOne::Update()
{
	{
		POINT nowPos = {};
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength = {};

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる

		if (nowLength.y <= -m_pos.y + m_texSize.y / 2 && nowLength.y >= -m_pos.y - m_texSize.y / 2
			&& nowLength.x >= m_pos.x - m_texSize.x / 2 && nowLength.x <= m_pos.x + m_texSize.x / 2)
		{
			m_color = { 1,1,1,0.5f };
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (m_key == false)
				{
					Fade::Instance().BootBlackFade(SceneManager::SceneType::Game);
					//SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
					m_key = true;
				}
			}
			else
			{
				m_key = false;
			}
		}
		else
		{
			m_color = { 1,1,1,1 };
		}
	}
}
