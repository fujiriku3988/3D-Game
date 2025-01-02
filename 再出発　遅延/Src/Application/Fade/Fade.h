#pragma once

#include "../Scene/SceneManager.h"

class Fade
{
public:

	void Update();
	void Draw();

	void UpdateBlackFade();
	void UpdateWhiteFade();

	void BootBlackFade(SceneManager::SceneType _type);
	void BootWhiteFade(SceneManager::SceneType _type);

	bool GetFade() { return m_bFade; }
private:

	void Init();

	SceneManager::SceneType m_nextScene;

	bool m_bFade;			// �t�F�[�h�����ǂ����H
	bool m_bFadeOut;		// �t�F�[�h�A�E�g�H
	bool m_bFadeIn;			// �t�F�[�h�C���H
	bool m_bColor;			// ���������H(true ��:false ��)

	// ��(1280*720)
	KdTexture m_blackTex;
	Math::Matrix m_blackMat;
	Math::Color m_blackColor;
	float m_blackAlpha;
	
	// ��(1280*720)
	KdTexture m_whiteTex;
	Math::Matrix m_whiteMat;
	Math::Color m_whiteColor;
	float m_whiteAlpha;

private:

	Fade() { Init(); }
	~Fade() {}

public:

	static Fade& Instance()
	{
		static Fade instance;
		return instance;
	}
};