#include "GameClear.h"
#include"../../Fade/Fade.h"

void GameClear::Init()
{
	m_tex.Load("Asset/Textures/obj/Text/gameclear02.png");
	m_spritePos = {};
	m_scale = {2};
	m_texSize = { 355,79 };
	m_time = 120.0f;
	m_alpha = 0.0f;
	m_alphaMAX = 1.0f;
	m_alphaSpeed = 0.001f;
	m_color = { 1.0f,1.0f,1.0f,m_alpha };
}

void GameClear::Update()
{
	m_time--;
	m_alpha += m_alphaSpeed;

	if (m_time <= 0)
	{
		m_time = 0;
	}

	if (m_time == 0)
	{
		Fade::Instance().BootBlackFade(SceneManager::SceneType::Title);
	}
	if (m_alpha >= m_alphaMAX)
	{
		m_alpha = m_alphaMAX;
	}
}

void GameClear::DrawSprite()
{
	m_color = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_spritePos.x, m_spritePos.y, 
														m_texSize .x*m_scale.x, m_texSize .y* m_scale.y,
														nullptr, &m_color);
}
