#include "NumTwo.h"
#include"../../../../main.h"

#include "../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void NumTwo::Init(const std::string _filePath)
{
	m_tex.Load("Asset/Textures/UI/Text/number.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "NumTwo", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "NumTwo", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "NumTwo", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "NumTwo", "texSizeHarf");
	m_anim = JsonManager::Instance().GetParamVec2(_filePath, "NumTwo", "anim");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "NumTwo", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "NumTwo", "drawFlg");
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Text/NumTwo.json", "NumTwo", "anim", m_anim);
}

void NumTwo::DrawSprite()
{
	m_rect = { (long)m_texSize.x * (long)m_anim.x,(long)m_texSize.y * (long)m_anim.y,
				(long)m_texSize.x ,(long)m_texSize.y };

	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, &m_rect, &m_color);
	}
}

void NumTwo::Update()
{
	POINT nowPos = {};
	GetCursorPos(&nowPos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	POINT nowLength = {};

	nowLength.x = (nowPos.x - NumberConstants::WindowSizeWidth);//マウス座標の(0,0)の位置が画面左上の端だから補正
	nowLength.y = (nowPos.y - NumberConstants::WindowSizeHeight);//マウス座標の(0,0)の位置が画面左上の端だから補正

	if (nowLength.y <= -m_pos.y + m_texSizeHarf.y && nowLength.y >= -m_pos.y - m_texSizeHarf.y
		&& nowLength.x >= m_pos.x - m_texSizeHarf.x && nowLength.x <= m_pos.x + m_texSizeHarf.x)
	{
		m_color.w = NumberConstants::AlphaSemiTransparent;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_key == false)
			{
				Fade::Instance().BootBlackFade(SceneManager::SceneType::Stage2);
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
