#include "Restart.h"
#include"../../../../main.h"

void Restart::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/restart.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Restart", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "Restart", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Restart", "drawFlg");
}

void Restart::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void Restart::Update()
{
	//α値変更
	//m_alpha += m_speed;
	if (m_alpha < m_alphaMIN)
	{
		//m_speed *= -1;
	}
	if (m_alpha > m_alphaMAX)
	{
		//m_speed *= -1;
	}

	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる

		if (nowLength.y <= -m_pos.y + 40 && nowLength.y >= -m_pos.y - 40
			&& nowLength.x >= m_pos.x - 45 && nowLength.x <= m_pos.x + 45)
		{
			m_scale.x += 0.05f;
			m_scale.y += 0.05f;
			if (m_scale.x >= 1.2f) { m_scale.x = 1.2f; }
			if (m_scale.y >= 1.2f) { m_scale.y = 1.2f; }
		}
		else
		{
			m_scale = { 1.0f };
		}
	}
}
