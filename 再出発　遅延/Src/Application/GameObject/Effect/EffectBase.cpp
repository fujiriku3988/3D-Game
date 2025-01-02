#include "EffectBase.h"

void EffectBase::Init(const std::string _filePath)
{
	m_tex = std::make_shared<KdTexture>();
	m_poly = std::make_shared<KdSquarePolygon>();
}

void EffectBase::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_poly = std::make_shared<KdSquarePolygon>();

	m_pos = {};//座標
	m_rot = {};//回転値
	m_scale = {};//拡縮値

	m_sprPos = {};
	m_sprScale = {};
	m_texSize = {};
	m_color = { 1,1,1,1 };

	m_anime.count = 0;
	m_anime.speed = 0;
	m_anime.MAX = 0;
	m_anime.MIN = 0;

	Math::Matrix m_scaleMat = Math::Matrix::Identity;//拡縮
	Math::Matrix m_transMat = Math::Matrix::Identity;//移動
	Math::Matrix m_rotationMat = Math::Matrix::Identity;//回転
	Math::Matrix m_rotMatX = Math::Matrix::Identity;//回転X
	Math::Matrix m_rotMatY = Math::Matrix::Identity;//回転Y
	Math::Matrix m_rotMatZ = Math::Matrix::Identity;//回転Z

	/*m_sprPos = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "pos");
	m_sprScale = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "texSize");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "drawFlg");
	m_time = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "time");
	m_alpha = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alpha");
	m_alphaMAX = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alphaMAX");
	m_alphaMIN = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/UIBase.json", "UIBase", "alphaMIN");*/
}

void EffectBase::DrawSprite()
{
	if (m_drawFlg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
}

void EffectBase::DrawUnLit()
{
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
	}
}

void EffectBase::Update()
{
}

void EffectBase::ToggleDraw()
{
	m_drawFlg = !m_drawFlg;
}
