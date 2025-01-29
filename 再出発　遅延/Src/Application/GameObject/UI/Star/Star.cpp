#include "Star.h"
#include"../../../main.h"

#include"../../UI/GameTime/GameTime.h"

void Star::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/star.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "Star", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "Star", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "Star", "texSize");
	m_alpha = JsonManager::Instance().GetParam<float>(_filePath, "Star", "alpha");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Star", "drawFlg");
	m_rgb = JsonManager::Instance().GetParamVec3(_filePath, "Star", "rgb");

	m_effTex.Load("Asset/Textures/Effect/firework.png");
	m_effPos = JsonManager::Instance().GetParamVec2(_filePath, "Star", "effPos");
	m_effScale = JsonManager::Instance().GetParamVec2(_filePath, "Star", "effScale");
	m_effTexSize = JsonManager::Instance().GetParamVec2(_filePath, "Star", "effTexSize");
	m_effColor = JsonManager::Instance().GetParamVec4(_filePath, "Star", "effColor");
	m_anim = JsonManager::Instance().GetParamVec2(_filePath, "Star", "anim");
	m_animDelay = JsonManager::Instance().GetParam<float>(_filePath, "Star", "animDelay");
	m_clearTime = JsonManager::Instance().GetParam<float>(_filePath, "Star", "clearTime");
	m_animFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Star", "animFlg");
	m_clearFlg = JsonManager::Instance().GetParam<bool>(_filePath, "Star", "clearFlg");
	m_seFlg = false;

	m_filePath = _filePath;
}

void Star::DrawSprite()
{
	m_color = { m_rgb.x,m_rgb.y,m_rgb.z,m_alpha };
	m_effRect = { (long)m_effTexSize.x * (long)m_anim.x,(long)m_effTexSize.y * (long)m_anim.y,
				(long)m_effTexSize.x ,(long)m_effTexSize.y };
	if (m_drawFlg)
	{
		if (m_clearFlg)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
				m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
			if (m_animFlg)
			{
				KdShaderManager::Instance().m_spriteShader.DrawTex(&m_effTex, m_effPos.x, m_effPos.y,
					m_effTexSize.x * m_effScale.x, m_effTexSize.y * m_effScale.y, &m_effRect, &m_effColor);
			}
		}
	}
}

void Star::Update()
{
	//定数
	constexpr float ScaleMAX = 1.5f;
	//スプレッドシートX軸
	constexpr int MaxAnimaSideX = 6;
	//スプレッドシートY軸
	constexpr int MaxAnimaSideY = 5;
	//変化量
	constexpr float AlphaChangeAmount = 0.1f;
	constexpr float ScaleChangeAmount = 0.05f;

	if (m_drawFlg)
	{
		if (std::shared_ptr<GameTime>spGameTime = m_wpGameTime.lock())
		{
			if (m_clearTime >= spGameTime->GetNowTime())
			{
				m_clearFlg = true;
			}
		}
	}

	if (m_clearFlg)
	{
		if (!m_animFlg)
		{
			m_scale.x -= ScaleChangeAmount;
			m_scale.y -= ScaleChangeAmount;
			m_alpha += AlphaChangeAmount;
		}

		if (!m_seFlg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/star.wav", false, KdAudioManager::Instance().GetSEVolume());
		}
		m_seFlg = true;

		if (m_alpha >= NumberConstants::NumOne)
		{
			m_alpha = NumberConstants::NumOne;
		}

		if (m_scale.x <= ScaleMAX && m_scale.y <= ScaleMAX)
		{
			m_scale.x = ScaleMAX;
			m_scale.y = ScaleMAX;
			m_animFlg = true;
		}

		if (m_animFlg)
		{
			m_animDelay++;
			if (m_animDelay > NumberConstants::NumOne)
			{
				m_anim.x += NumberConstants::NumOne;
				m_animDelay = NumberConstants::NumZero;
			}

			if (m_anim.x >= MaxAnimaSideX)
			{
				m_anim.y += NumberConstants::NumOne;
				m_anim.x = NumberConstants::NumZero;
			}
			if (m_anim.y > MaxAnimaSideY)
			{
				m_anim.x = MaxAnimaSideX;
				m_animDelay = NumberConstants::NumZero;
			}
		}
	}
}

void Star::Restart()
{
	Init(m_filePath);
}
