#include "GuideTXT.h"
#include "GuideTXT.h"
#include"../../../../main.h"
#include"../../../../GameObject/UI/UIBase.h"

#include "../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void GuideTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/guide.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "GuideTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "GuideTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "GuideTXT", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "GuideTXT", "texSizeHarf");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "GuideTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "GuideTXT", "drawFlg");
	m_fadeFlg = JsonManager::Instance().GetParam<bool>(_filePath, "GuideTXT", "fadeFlg");
	m_fadeAlpha = JsonManager::Instance().GetParam<float>(_filePath, "GuideTXT", "fadeAlpha");
}

void GuideTXT::DrawSprite()
{
	if (m_drawFlg == true)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void GuideTXT::Update()
{
	//フェード中か？
	bool nowFadeFlg = Fade::Instance().GetFade();
	//フェード中なら早期リターン
	if (nowFadeFlg == true) { return; }
	//描画されていないなら処理を通さないために早期リターン
	if (m_drawFlg == false) { return; }

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
				KdAudioManager::Instance().Play("Asset/Sounds/SE/click.wav", false, KdAudioManager::Instance().GetSEVolume());

				SceneManager::Instance().SetNextScene(SceneManager::SceneType::Guide);

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
