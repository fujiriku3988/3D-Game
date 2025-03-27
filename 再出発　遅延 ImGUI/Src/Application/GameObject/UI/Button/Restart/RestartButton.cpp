#include "RestartButton.h"
#include"../../../../main.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void RestartButton::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Button/restart.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Restart", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Restart", "drawFlg");
	m_scaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Restart", "scaleMAX");
	m_filePath = _filePath;
}

void RestartButton::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void RestartButton::Update()
{
	//フェード中か？
	bool nowFadeFlg = Fade::Instance().GetFade();
	//フェード中なら早期リターン
	if (nowFadeFlg == true) { return; }
	//描画されていないなら処理を通さないために早期リターン
	//if (m_drawFlg == false) { return; }

	//定数
	//変化量
	constexpr float ScaleChangeAmount = 0.05f;

	//Rキー押したら
	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (m_keyFlg == false)
		{
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				obj->Restart();
			}
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
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
				for (auto& obj : SceneManager::Instance().GetObjList())
				{
					obj->Restart();
				}
				m_mouseKeyFlg = true;
			}
		}
		else
		{
			m_mouseKeyFlg = false;
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

void RestartButton::Restart()
{
	Init(m_filePath);
}
