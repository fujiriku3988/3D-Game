#include "VolumeSliderBGM.h"
#include"../../../../main.h"
#include"../../../../Scene/SceneManager.h"
#include"../../../../Fade/Fade.h"

void VolumeSliderBGM::Init(const std::string _filePath)
{
	UIBase::Init();
	m_handleTex.Load("Asset/Textures/UI/Sound/slideHandle.png");
	m_whiteSlideTex.Load("Asset/Textures/UI/Sound/slideWhite.png");
	m_blueSlideTex.Load("Asset/Textures/UI/Sound/slideBlue.png");
	//スライダー用変数（青）
	m_bluePos = JsonManager::Instance().GetParamVec2(_filePath, "bSlider", "pos");
	m_blueScale = JsonManager::Instance().GetParamVec2(_filePath, "bSlider", "scale");
	m_blueTexSize = JsonManager::Instance().GetParamVec2(_filePath, "bSlider", "texSize");
	m_blueTexSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "bSlider", "texSizeHarf");
	m_blueColor = JsonManager::Instance().GetParamVec4(_filePath, "bSlider", "color");
	//青スライダー専用
	m_blueDrawAdjust = JsonManager::Instance().GetParamVec2(_filePath, "bSlider", "drawAdjust");
	//スライダー用変数（白）
	m_whitePos = JsonManager::Instance().GetParamVec2(_filePath, "wSlider", "pos");
	m_whiteScale = JsonManager::Instance().GetParamVec2(_filePath, "wSlider", "scale");
	m_whiteTexSize = JsonManager::Instance().GetParamVec2(_filePath, "wSlider", "texSize");
	m_whiteColor = JsonManager::Instance().GetParamVec4(_filePath, "wSlider", "color");

	//ハンドル用
	m_handlePos = JsonManager::Instance().GetParamVec2(_filePath, "handle", "pos");
	m_handleScale = JsonManager::Instance().GetParamVec2(_filePath, "handle", "scale");
	m_handleTexSize = JsonManager::Instance().GetParamVec2(_filePath, "handle", "texSize");
	m_handleTexSizeHarf = JsonManager::Instance().GetParamVec2(_filePath, "handle", "texSizeHarf");

	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "other", "drawFlg");
	m_filePath = _filePath;
}

void VolumeSliderBGM::DrawSprite()
{
	//青いスライドだけに適用
	//切り取り位置、切り取り範囲
	Math::Rectangle slideRect = { NumberConstants::NumZero,NumberConstants::NumZero,
		(long)m_blueTexSize.x + (int)m_blueDrawAdjust.x,(long)m_blueTexSize.y };
	//描画
	if (m_drawFlg == true)
	{
		//白のスライド
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_whiteSlideTex, m_whitePos.x, m_whitePos.y,
			m_whiteTexSize.x * m_whiteScale.x, m_whiteTexSize.y * m_whiteScale.y, nullptr, &m_whiteColor);

		//青のスライド
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_blueSlideTex,
			m_bluePos.x + (m_blueDrawAdjust.x / NumberConstants::NumTwo), m_bluePos.y,
			m_blueTexSize.x + m_blueDrawAdjust.x, m_blueTexSize.y, &slideRect, &m_blueColor);

		//ハンドル
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_handleTex, m_handlePos.x, m_handlePos.y,
			m_handleTexSize.x * m_handleScale.x, m_handleTexSize.y * m_handleScale.y, nullptr, &m_color, { 0.5,0.5 });
	}

}

void VolumeSliderBGM::Update()
{
	//マウス座標
	POINT nowPos;
	//マウス座標取得
	GetCursorPos(&nowPos);
	//ウィンドウの場所から座標をとる
	//ウィンドウをずらしても正常に
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	//実際の画面に補正する変数
	POINT nowLength;
	//マウス座標の(0,0)の位置が画面左上の端だから補正
	//画面中央を(0,0)として考えて補正
	nowLength.x = (nowPos.x - NumberConstants::WindowSizeWidth);
	nowLength.y = (nowPos.y - NumberConstants::WindowSizeHeight);

	WirteJsonFile();
	MoveHandle(nowLength);

	//ハンドルの位置で変わる割合：((中心から左右へのの絶対値96)+ハンドルの座標)÷(スライドバー全体192)
	float volume = (m_blueTexSizeHarf.x + m_handlePos.x) / m_blueTexSize.x;

	KdAudioManager::Instance().UpdateBGMVolume(volume);

	m_blueDrawAdjust.x = m_handlePos.x - m_blueTexSizeHarf.x;
}

void VolumeSliderBGM::WirteJsonFile()
{
	//動かす前の座標と動かしたあとの座標が違っていたらJSONファイルに書き込み
	if (m_handleCurrentPos != m_handlePos)
	{
		JsonManager::Instance().AddParamVec2(m_filePath, "handle", "pos", m_handlePos);
	}
	//書き込んだあとに座標を記憶
	m_handleCurrentPos = m_handlePos;
}

void VolumeSliderBGM::MoveHandle(const POINT _pos)
{
	if (m_drawFlg == false) return;

	// すでに他のスライダーが操作中なら、自分の範囲外で return する
	if (UIBase::m_activeSlider != nullptr && UIBase::m_activeSlider != this)
	{
		if (!(_pos.y <= -m_handlePos.y + m_handleTexSize.y && _pos.y >= -m_handlePos.y - m_handleTexSize.y
			&& _pos.x >= m_handlePos.x - m_handleTexSize.x && _pos.x <= m_handlePos.x + m_handleTexSize.x))
		{
			return;
		}
	}

	// 左クリックが押されたらハンドルをつかむ
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// 他のスライダーが操作中でも、自分の範囲内なら m_activeSlider を更新
		UIBase::m_activeSlider = this;

		if (m_dragFlg == true ||
			(_pos.y <= -m_handlePos.y + m_handleTexSize.y && _pos.y >= -m_handlePos.y - m_handleTexSize.y
				&& _pos.x >= m_handlePos.x - m_handleTexSize.x && _pos.x <= m_handlePos.x + m_handleTexSize.x))
		{
			if (m_dragFlg == false)
			{
				KdAudioManager::Instance().Play("Asset/Sounds/SE/click.wav", false, KdAudioManager::Instance().GetSEVolume());
			}
			m_dragFlg = true;
			m_handlePos.x = _pos.x;

			if (m_handlePos.x > m_blueTexSizeHarf.x) m_handlePos.x = m_blueTexSizeHarf.x;
			else if (m_handlePos.x < -m_blueTexSizeHarf.x) m_handlePos.x = -m_blueTexSizeHarf.x;
		}
	}
	else
	{
		m_dragFlg = false;
		if (UIBase::m_activeSlider == this)
		{
			UIBase::m_activeSlider = nullptr;
		}
	}
}
