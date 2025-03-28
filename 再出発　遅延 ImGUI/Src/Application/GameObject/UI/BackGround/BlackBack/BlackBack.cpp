﻿#include "BlackBack.h"

void BlackBack::Init(const std::string _filePath)
{
	UIBase::Init();
	m_tex.Load("Asset/Textures/UI/Back/black.png");
	m_pos = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "pos");
	m_scale = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "scale");
	m_texSize = JsonManager::Instance().GetParamVec2(_filePath, "BlackBack", "texSize");
	m_color = JsonManager::Instance().GetParamVec4(_filePath, "BlackBack", "color");
	m_drawFlg = JsonManager::Instance().GetParam<bool>(_filePath, "BlackBack", "drawFlg");
	m_filePath = _filePath;
}

void BlackBack::DrawSprite()
{
	//描画処理
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y,
			(int)m_texSize.x * (int)m_scale.x, (int)m_texSize.y * (int)m_scale.y, nullptr, &m_color);
	}
}

void BlackBack::Update()
{
}

void BlackBack::Restart()
{
	//リスタート処理
	Init(m_filePath);
}
