#include "BackButton.h"
#include"../../../../main.h"
#include"../../../../GameObject/UI/UIBase.h"

#include"../../../../Fade/Fade.h"
#include"../../../../Scene/SceneManager.h"

void BackButton::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Button/return.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Back", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Back", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Back", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Back", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Back", "drawFlg");
	m_scaleMAX = JsonManager::Instance().GetParam<float>(_filePath, "Back", "scaleMAX");
	m_filePath = _filePath;
}

void BackButton::DrawSprite()
{
	//描画処理
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void BackButton::Update()
{
	//定数
	//変化量
	constexpr float ScaleChangeAmount = 0.05f;

	//描画しているなら
	if (m_drawFlg)
	{
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
				if (m_key == false)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/SE/click.wav", false, KdAudioManager::Instance().GetSEVolume());
					SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
					m_key = true;
				}
			}
			else
			{
				m_key = false;
			}

			//拡縮値の変更
			m_scale.x += ScaleChangeAmount;
			m_scale.y += ScaleChangeAmount;
			if (m_scale.x >= m_scaleMAX) { m_scale.x = m_scaleMAX; }
			if (m_scale.y >= m_scaleMAX) { m_scale.y = m_scaleMAX; }
		}
		else
		{
			m_scale = JsonManager::Instance().GetParamVec2(m_filePath, "Back", "scale");
		}
	}
}