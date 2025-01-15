#include "EffectBase.h"

void EffectBase::Init(const std::string _filePath)
{
}

void EffectBase::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_poly = std::make_shared<KdSquarePolygon>();

	m_pos = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "pos");
	m_rot = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "rot");
	m_scale = JsonManager::Instance().GetParamVec3("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "scale");
	m_color = JsonManager::Instance().GetParamVec4("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "color");

	m_anime.count = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "animCnt");
	m_anime.speed = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "animSpd");
	m_anime.MAX = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "animMAX");
	m_anime.MIN = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "animMIN");

	m_sprPos = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "sprPos");
	m_sprScale = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "sprScale");
	m_texSize = JsonManager::Instance().GetParamVec2("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "texSize");
	m_drawFlg = JsonManager::Instance().GetParam<bool>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "drawFlg");
	m_time = JsonManager::Instance().GetParam<int>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "time");
	m_alpha = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "alpha");
	m_alphaMAX = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "alphaMAX");
	m_alphaMIN = JsonManager::Instance().GetParam<float>("Asset/Data/Json/BaseFile/EffectBase.json", "EffectBase", "alphaMIN");

	m_scaleMat = Math::Matrix::Identity;//拡縮
	m_transMat = Math::Matrix::Identity;//移動
	m_rotationMat = Math::Matrix::Identity;//回転
	m_rotMatX = Math::Matrix::Identity;//回転X
	m_rotMatY = Math::Matrix::Identity;//回転Y
	m_rotMatZ = Math::Matrix::Identity;//回転Z
}

void EffectBase::DrawSprite()
{
	if (m_drawFlg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, (int)m_pos.x, (int)m_pos.y,
		(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
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
