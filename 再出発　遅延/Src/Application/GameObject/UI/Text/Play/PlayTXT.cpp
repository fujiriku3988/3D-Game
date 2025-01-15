#include "PlayTXT.h"
#include"../../../../main.h"

#include "../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void PlayTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/play.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "PlayTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "PlayTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "PlayTXT", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "PlayTXT", "texSizeHarf");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "PlayTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "PlayTXT", "drawFlg");
	m_fadeAlpha = JsonManager::Instance().GetParam<float>(_filePath, "PlayTXT", "fadeAlpha");
}

void PlayTXT::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (float)m_pos.x, (float)m_pos.y,
			(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
	}
}

void PlayTXT::Update()
{
	float alpha = Fade::Instance().GetBlackAlpha();

	{
		POINT nowPos = {};
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength = {};

		nowLength.x = (nowPos.x - NumberConstants::WindowSizeWidth);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - NumberConstants::WindowSizeHeight);//マウス座標の(0,0)の位置が画面左上の端だから補正

		if (alpha <= m_fadeAlpha)
		{
			if (nowLength.y <= -m_pos.y + m_texSizeHarf.y && nowLength.y >= -m_pos.y - m_texSizeHarf.y
				&& nowLength.x >= m_pos.x - m_texSizeHarf.x && nowLength.x <= m_pos.x + m_texSizeHarf.x)
			{
				m_color.w = NumberConstants::AlphaSemiTransparent;
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					if (m_key == false)
					{
						SceneManager::Instance().SetNextScene(SceneManager::SceneType::StageSelectScene);
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
				m_color.w = NumberConstants::AlphaVisible;
			}
		}
	}
}
