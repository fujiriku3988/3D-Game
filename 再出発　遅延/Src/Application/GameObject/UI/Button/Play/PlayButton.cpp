#include "PlayButton.h"
#include"../../../../main.h"

void PlayButton::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/Play.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Play", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Play", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Play", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Play", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Play", "drawFlg");
	m_scaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Play", "scaleMAX");
	m_filePath = _filePath;
}

void PlayButton::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void PlayButton::Update()
{
	{
		//定数
		//変化量
		constexpr float ScaleChangeAmount = 0.05f;

		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - NumberConstants::WindowSizeWidth);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - NumberConstants::WindowSizeHeight);//マウス座標の(0,0)の位置が画面左上の端だから補正

		if (nowLength.y <= -m_pos.y + m_texSize.y && nowLength.y >= -m_pos.y - m_texSize.y
			&& nowLength.x >= m_pos.x - m_texSize.x && nowLength.x <= m_pos.x + m_texSize.x)
		{
			m_scale.x += ScaleChangeAmount;
			m_scale.y += ScaleChangeAmount;
			if (m_scale.x >= m_scaleMAX) { m_scale.x = m_scaleMAX; }
			if (m_scale.y >= m_scaleMAX) { m_scale.y = m_scaleMAX; }
		}
		else
		{
			m_scale = { NumberConstants::AlphaVisible };
		}
	}
}

void PlayButton::Restart()
{
	Init(m_filePath);
}
