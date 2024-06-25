#include "Title.h"

void Title::Init()
{
	m_tex.Load("Asset/Textures/obj/Text/title01.png");
	m_spritePos = {0,200};
	m_scale = {1.5};
	m_texSize = {812,87};
	m_alpha = 1.0f;
	m_color = { 1.0f,1.0f,1.0f,1.0f };
}

void Title::Update()
{
}

void Title::DrawSprite()
{
	m_color = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_spritePos.x, m_spritePos.y,
														m_texSize.x * m_scale.x, m_texSize.y * m_scale.y,
														nullptr, &m_color);
}
