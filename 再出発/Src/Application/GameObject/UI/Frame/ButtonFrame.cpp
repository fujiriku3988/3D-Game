#include "ButtonFrame.h"

void ButtonFrame::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/buttonFrame.png");

	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "ButtonFrame", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "ButtonFrame", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "ButtonFrame", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "ButtonFrame", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "ButtonFrame", "drawFlg");
}

void ButtonFrame::Init()
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Result/buttonFrame.png");
	m_pos = { 40,-150 };
	m_scale = { 1.0f };
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
	m_texSize = { 192,64 };

	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Frame/ButtonFrame1.json", "ButtonFrame", "pos", m_pos);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Frame/ButtonFrame1.json", "ButtonFrame", "scale", m_scale);
	JsonManager::Instance().AddParamVec2("Asset/Data/Json/UI/Frame/ButtonFrame1.json", "ButtonFrame", "texSize", m_texSize);
	JsonManager::Instance().AddParamVec4("Asset/Data/Json/UI/Frame/ButtonFrame1.json", "ButtonFrame", "color", m_color);
	JsonManager::Instance().AddParam<bool>("Asset/Data/Json/UI/Frame/ButtonFrame1.json", "ButtonFrame", "drawFlg", m_drawFlg);
}

void ButtonFrame::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y,nullptr, &m_color);
	}
}

void ButtonFrame::Update()
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
}
