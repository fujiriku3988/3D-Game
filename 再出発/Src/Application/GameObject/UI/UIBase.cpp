#include "UIBase.h"

void UIBase::Init(const std::string _filePath)
{

}

void UIBase::Init()
{
	m_pos = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "pos");
	m_scale = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "texSize");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "drawFlg");
	m_time = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "time");
	m_alpha = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alpha");
	m_alphaMAX = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alphaMAX");
	m_alphaMIN = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alphaMIN");
}

void UIBase::DrawSprite()
{
	if (m_drawFlg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
}

void UIBase::Update()
{
}
