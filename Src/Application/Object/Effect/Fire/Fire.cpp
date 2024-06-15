#include "Fire.h"

void Fire::Init()
{
	BaseEffect::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy01/fire01.png");
	m_pos = { 0,6,0};
	m_scale = { 1 };
	m_speed = 0.1f;
	//m_poly->SetSplit(3, 4);
	//m_poly->SetUVRect(0);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void Fire::PreUpdate()
{
}

void Fire::Update()
{
}

void Fire::PostUpdate()
{
	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	//rotMatY = Math::Matrix::CreateRotationY(30);
	m_mWorld = scaleMat * transMat;
}
