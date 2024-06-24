#include "Click.h"
#include"../../Fade/Fade.h"

void Click::Init()
{
	m_tex.Load("Asset/Textures/obj/Text/click04.png");
	m_spritePos = { 0,0 };
	m_scale = { 1 };
	m_texSize = { 496,75 };
	m_alpha = 1.0f;
	speed = -0.01f;
	m_clickFlg = false;
	m_color = { 1.0f,1.0f,1.0f,1.0f };
}

void Click::Update()
{
	if (!m_clickFlg)
	{

		//α値変更
		m_alpha += speed;
		if (m_alpha < 0.4f)
		{
			speed *= -1;
		}
		if (m_alpha > 1.0f)
		{
			speed *= -1;
		}
	}
	else
	{
		speed = -0.01f;
		m_alpha += speed;
		if (m_alpha <= 0)
		{
			m_alpha = 0;
		}
		if (m_alpha == 0) { Fade::Instance().BootBlackFade(SceneManager::SceneType::Game); }
	}
	
}

void Click::DrawSprite()
{
	m_color = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_spritePos.x, m_spritePos.y,
														m_texSize.x * m_scale.x, m_texSize.y * m_scale.y,
														nullptr, &m_color);
}
