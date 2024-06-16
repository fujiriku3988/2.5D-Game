#include "Hp.h"

void Hp::Init()
{
	CharacterBase::Init();
	//m_poly = std::make_shared<KdSquarePolygon>();
	//m_poly->SetMaterial("Asset/Textures/obj/player/hp01.png");
	m_tex.Load("Asset/Textures/obj/player/hp01.png");
	m_pos = { 0,5,0 };
	m_scale = { 5.0 };
	m_anime = 0;
	m_hp = 2;
	m_animeSpeed = 0.08f;
	//m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_color = { 1,1,1,1 };
}

void Hp::PreUpdate()
{
}

void Hp::Update()
{
}

void Hp::PostUpdate()
{
	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(0);
	m_mWorld = scaleMat * rotMatX * transMat;
}

void Hp::GenerateDepthMapFromLight()
{
}

void Hp::DrawLit()
{
}

void Hp::DrawSprite()
{
	Math::Rectangle rect = { 0,0,32,32 };
	Math::Color color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x,m_pos.y, 32, 32, &rect, &color);
}
