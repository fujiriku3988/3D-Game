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
	m_scaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Return", "scaleMAX");
	m_filePath = _filePath;
}

void ReturnButton::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (float)m_pos.x, (float)m_pos.y,
			(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void ReturnButton::Update()
{
	//定数
	//変化量
	constexpr float ScaleChangeAmount = 0.05f;

	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - NumberConstants::WindowSizeWidth);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - NumberConstants::WindowSizeHeight);//マウス座標の(0,0)の位置が画面左上の端だから補正

		if (nowLength.y <= -m_pos.y + m_texSize.y && nowLength.y >= -m_pos.y - m_texSize.y
			&& nowLength.x >= m_pos.x - m_texSize.x && nowLength.x <= m_pos.x + m_texSize.x)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				Fade::Instance().BootBlackFade(SceneManager::SceneType::Title);
			}

			m_scale.x += ScaleChangeAmount;
			m_scale.y += ScaleChangeAmount;
			if (m_scale.x >= m_scaleMAX) { m_scale.x = m_scaleMAX; }
			if (m_scale.y >= m_scaleMAX) { m_scale.y = m_scaleMAX; }
		}
		else
		{
			m_scale = { NumberConstants::NumOne };
		}
	}
}

void ReturnButton::Restart()
{
	Init(m_filePath);
}
