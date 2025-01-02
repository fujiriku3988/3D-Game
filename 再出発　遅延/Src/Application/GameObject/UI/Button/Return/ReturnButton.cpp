#include "ReturnButton.h"
#include"../../../../main.h"

#include"../../../../Fade/Fade.h"
#include"../../../../Scene/SceneManager.h"

void ReturnButton::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/return.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Return", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Return", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Return", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Return", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Return", "drawFlg");
	m_filePath = _filePath;
}

void ReturnButton::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void ReturnButton::Update()
{
	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる

		if (nowLength.y <= -m_pos.y + m_texSize.y && nowLength.y >= -m_pos.y - m_texSize.y
			&& nowLength.x >= m_pos.x - m_texSize.x && nowLength.x <= m_pos.x + m_texSize.x)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				Fade::Instance().BootBlackFade(SceneManager::SceneType::Title);
			}

			m_scale.x += 0.05f;
			m_scale.y += 0.05f;
			if (m_scale.x >= 1.2f) { m_scale.x = 1.2f; }
			if (m_scale.y >= 1.2f) { m_scale.y = 1.2f; }
		}
		else
		{
			m_scale = { 1.0f };
		}
	}
}

void ReturnButton::Restart()
{
	Init(m_filePath);
}
