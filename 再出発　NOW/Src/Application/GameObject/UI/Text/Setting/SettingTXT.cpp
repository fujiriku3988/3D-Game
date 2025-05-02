#include "SettingTXT.h"
#include"../../../../main.h"

#include "../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void SettingTXT::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Text/setting.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "SettingTXT", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "SettingTXT", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "SettingTXT", "texSize");
	m_texSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "SettingTXT", "texSizeHarf");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "SettingTXT", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "SettingTXT", "drawFlg");
	m_fadeAlpha = JsonManager::Instance().GetParam<float>(_filePath, "SettingTXT", "fadeAlpha");
}

void SettingTXT::DrawSprite()
{
	if (m_drawFlg == true)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void SettingTXT::Update()
{
	//フェード中か？
	bool nowFadeFlg = Fade::Instance().GetFade();
	//フェード中なら早期リターン
	if (nowFadeFlg == true) { return; }
	//描画されていないなら処理を通さないために早期リターン
	if (m_drawFlg == false) { return; }

	//マウス座標
	POINT nowPos;
	//マウス座標取得
	GetCursorPos(&nowPos);
	//ウィンドウの場所から座標をとる
	//ウィンドウをずらしても正常に
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	//実際の画面に補正した変数
	POINT nowLength;

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
				SceneManager::Instance().SetNextScene(SceneManager::SceneType::Setting);
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
