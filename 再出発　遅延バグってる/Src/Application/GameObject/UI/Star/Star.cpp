#include "Star.h"
#include"../../../main.h"

#include"../../UI/GameTime/GameTime.h"

void Star::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Star/star1.png");
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
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
				(int)m_texSize.x * (float)m_scale.x, (int)m_texSize.y * (float)m_scale.y, nullptr, &m_color);
			if (m_animFlg)
			{
				KdShaderManager::Instance().m_spriteShader.DrawTex(&m_effTex, (int)m_effPos.x, (int)m_effPos.y,
					(int)m_effTexSize.x * (int)m_effScale.x, (int)m_effTexSize.y * (int)m_effScale.y, &m_effRect, &m_effColor);
			}
		}
	}
}

void Star::Update()
{
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
			m_scale.x -= 0.05f;
			m_scale.y -= 0.05f;
			m_alpha += 0.1f;
		}

		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
		}

		if (m_scale.x <= 1.5f && m_scale.y <= 1.5f)
		{
			m_scale.x = 1.5f;
			m_scale.y = 1.5f;
			m_animFlg = true;
		}

		if (m_animFlg)
		{
			m_animDelay++;
			if (m_animDelay > 1)
			{
				m_anim.x += 1;
				m_animDelay = 0;
			}

			if (m_anim.x >= 6)
			{
				m_anim.y += 1;
				m_anim.x = 0;
			}
			if (m_anim.y > 5)
			{
				m_anim.x = 6;
				m_animDelay = 0;
			}
		}
	}
}

void Star::Restart()
{
	Init(m_filePath);
}
