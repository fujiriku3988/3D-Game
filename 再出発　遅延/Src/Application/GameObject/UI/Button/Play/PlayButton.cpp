#include "PlayButton.h"
#include"../../../../main.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void PlayButton::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Button/Play.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Play", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Play", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Play", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Play", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Play", "drawFlg");
	m_scaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Play", "scaleMAX");
	m_incrmentConst = NumberConstants::NumOne;
	m_filePath = _filePath;
}

void PlayButton::DrawSprite()
{
	//描画
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void PlayButton::Update()
{
	//フェード中か？
	bool nowFadeFlg = Fade::Instance().GetFade();
	//フェード中なら早期リターン
	if (nowFadeFlg == true) { return; }
	//描画されていないなら処理を通さないために早期リターン
	if (m_drawFlg == false) { return; }

	//定数
	//変化量
	constexpr float scaleChangeAmount = 0.05f;

	//エンターキー押したら
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_enterKeyFlg == false)
		{
			// 現在のシーン
			SceneManager::SceneType currentScene = SceneManager::Instance().GetSceneType();

			//次のシーンが範囲以内か？
			if (static_cast<int>(currentScene) + m_incrmentConst <= static_cast<int>(SceneManager::SceneType::Stage3))
			{
				//次のシーンに移行
				auto nextScene = SceneManager::Instance().IncrementSceneType(currentScene);
				Fade::Instance().BootBlackFade(nextScene);
			}
			else
			{
				return;
			}
			m_enterKeyFlg = true;
		}
	}
	else
	{
		m_enterKeyFlg = false;
	}

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

	if (nowLength.y <= -m_pos.y + m_texSize.y && nowLength.y >= -m_pos.y - m_texSize.y
		&& nowLength.x >= m_pos.x - m_texSize.x && nowLength.x <= m_pos.x + m_texSize.x)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_mouseKeyFlg == false)
			{
				// 現在のシーン
				SceneManager::SceneType currentScene = SceneManager::Instance().GetSceneType();

				//次のシーンが範囲以内か？
				if (static_cast<int>(currentScene) + m_incrmentConst <= static_cast<int>(SceneManager::SceneType::Stage3))
				{
					//次のシーンに移行
					auto nextScene = SceneManager::Instance().IncrementSceneType(currentScene);
					Fade::Instance().BootBlackFade(nextScene);
				}
				else
				{
					return;
				}
				m_mouseKeyFlg = true;
			}
		}
		else
		{
			m_mouseKeyFlg = false;
		}

		//拡縮値の変更
		m_scale.x += scaleChangeAmount;
		m_scale.y += scaleChangeAmount;
		if (m_scale.x >= m_scaleMAX) { m_scale.x = m_scaleMAX; }
		if (m_scale.y >= m_scaleMAX) { m_scale.y = m_scaleMAX; }
	}
	else
	{
		m_scale = { NumberConstants::AlphaVisible };
	}
}

void PlayButton::Restart()
{
	Init(m_filePath);
}
