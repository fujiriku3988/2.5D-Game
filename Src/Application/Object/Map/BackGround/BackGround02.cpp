#include "BackGround02.h"

void BackGround02::Init()
{
	m_tex01.Load("Asset/Textures/obj/back/forest01.png");//森
	m_pos = {};
	m_rot = {};
	m_scale = {};
	m_color = { 1,1,1,1 };
}

void BackGround02::Update()
{
	//m_pos.x += -1.0f;
}

void BackGround02::DrawSprite()
{
	m_color = { 1.2f,1.2f,1.2f,1 };
	m_rect = { 0, 0, 2304, 1536 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex01, m_pos.x+200, m_pos.y, 2304,1536, &m_rect, &m_color);
}

