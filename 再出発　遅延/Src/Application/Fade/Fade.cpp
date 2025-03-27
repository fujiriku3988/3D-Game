#include "Fade.h"

#include"../Scene/SceneManager.h"
#include"../main.h"

void Fade::Update()
{
	//ホワイトフェード
	if (m_bColor == true)UpdateWhiteFade();
	//ブラックフェード
	else if (m_bColor == false)UpdateBlackFade();

	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("bFade: %s\n", m_bFade ? "true" : "false");
	Application::Instance().m_log.AddLog("bColor: %s\n", m_bColor ? "true" : "false");
	Application::Instance().m_log.AddLog("m_bFadeOut: %s\n", m_bFadeOut ? "true" : "false");
	Application::Instance().m_log.AddLog("m_bFadeIn: %s\n", m_bFadeIn ? "true" : "false");
	Application::Instance().m_log.AddLog("Fade Update: m_bFade = %d, m_bColor = %d\n", m_bFade, m_bColor);
	Application::Instance().m_log.AddLog("FadeOut処理中: m_blackAlpha = %f\n", m_blackAlpha);
	Application::Instance().m_log.AddLog("BootBlackFade 実行: m_bFade = %d, m_bFadeOut = %d, m_bColor = %d\n", m_bFade, m_bFadeOut, m_bColor);
}

void Fade::Draw()
{
	//ホワイトフェード
	if (m_bColor == true)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_whiteTex, 0, 0, nullptr, &m_whiteColor);
	}
	//ブラックフェード
	else if (m_bColor == false)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_blackTex, 0, 0, nullptr, &m_blackColor);
	}
}

//ステージ切り替えやシーン切り替えに使おうかな
void Fade::UpdateBlackFade()
{
	//定数
	constexpr float incrementAlpha = 0.008f;
	//if (m_bFade)
	{
		//フェードアウト
		if (m_bFadeOut == true)
		{
			m_blackAlpha += incrementAlpha;
			//アルファ値が１以上なら
			if (m_blackAlpha >= NumberConstants::NumOne)
			{
				m_bFadeOut = false;
				m_blackAlpha = NumberConstants::NumOne;
				SceneManager::Instance().SetNextScene(m_nextScene);
				m_bFadeIn = true;
			}
			//m_blackColor.w = m_blackAlpha;
			m_blackColor = { 1.0f,1.0f,1.0f,m_blackAlpha };
		}
		//フェードイン
		if (m_bFadeIn == true)
		{
			m_blackAlpha -= incrementAlpha;
			//アルファ値が０以下なら
			if (m_blackAlpha <= NumberConstants::NumZero)
			{
				m_bFadeIn = false;
				m_blackAlpha = NumberConstants::NumZero;
				SceneManager::Instance().SetNextScene(m_nextScene);
				m_bFade = false;
			}
			//m_blackColor.w = m_blackAlpha;
			m_blackColor = { 1.0f,1.0f,1.0f,m_blackAlpha };
		}
	}
}

void Fade::UpdateWhiteFade()
{
	//定数
	constexpr float incrementAlpha = 0.008f;
	//フェードアウト
	if (m_bFadeOut == true)
	{
		m_whiteAlpha += incrementAlpha;
		//アルファ値が１以上なら
		if (m_whiteAlpha >= NumberConstants::NumOne)
		{
			m_bFadeOut = true;
			m_whiteAlpha = NumberConstants::NumOne;
			SceneManager::Instance().SetNextScene(m_nextScene);
			m_bFadeIn = true;
		}
		m_whiteColor.w = m_whiteAlpha;
	}
	//フェードイン
	if (m_bFadeIn == true)
	{
		m_whiteAlpha -= incrementAlpha;
		//アルファ値が０以下なら
		if (m_whiteAlpha <= NumberConstants::NumZero)
		{
			m_bFadeIn = false;
			m_whiteAlpha = NumberConstants::NumZero;
			m_bFade = false;
		}
		m_whiteColor.w = m_whiteAlpha;
	}
}

void Fade::BootBlackFade(SceneManager::SceneType _type)
{
	//各フラグを設定
	//ブラックフェードを使う時に使う
	m_bFade = true;
	m_bFadeOut = true;
	m_nextScene = _type;
	m_bColor = false;
}

void Fade::BootWhiteFade(SceneManager::SceneType _type)
{
	//各フラグを設定
	//ホワイトフェードを使う時に使う
	m_bFade = true;
	m_bFadeOut = true;
	m_nextScene = _type;
	m_bColor = true;
}

void Fade::Init()
{
	m_bFade = false;
	m_bFadeOut = false;
	m_bFadeIn = false;
	m_bColor = false;

	m_blackTex.Load("Asset/Textures/Fade/black.png");
	m_blackMat = Math::Matrix::Identity;
	m_blackAlpha = NumberConstants::NumZero;
	m_blackColor = JsonManager::Instance().GetParamVec4("Asset/Data/Json/Fade/Fade.json", "Fade", "blackColor");
	m_blackColor.w = m_blackAlpha;

	m_whiteTex.Load("Asset/Textures/Fade/white.png");
	m_whiteMat = Math::Matrix::Identity;
	m_whiteAlpha = NumberConstants::NumZero;
	m_whiteColor = JsonManager::Instance().GetParamVec4("Asset/Data/Json/Fade/Fade.json", "Fade", "whiteColor");
	m_whiteColor.w = m_whiteAlpha;
}
