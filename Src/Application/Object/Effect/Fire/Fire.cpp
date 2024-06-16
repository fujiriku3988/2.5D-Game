﻿#include "Fire.h"

void Fire::Init()
{
	BaseEffect::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy01/fire01.png");
	//m_poly.SetMaterial("Asset/Textures/obj/enemy01/fire01.png");
	m_pos = {};
	m_scale = { 1 };
	m_speed = 0.05f;
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	dissolve = 0;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("fire", { 0,0.5f,0 }, 0.3f, KdCollider::TypeDamage);
	m_objType = KdGameObject::FireAttack;
}

void Fire::DrawLit()
{
	dissolve += 0.006f;
	if (dissolve > 1)
	{
		dissolve = 1.00f;
	}
	KdShaderManager::Instance().m_StandardShader.SetDissolve(dissolve);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Fire::PreUpdate()
{
	
}

void Fire::Update()
{
	m_pDebugWire->AddDebugSphere(m_pos+Math::Vector3{0,0.5f,0}, 0.3f, kGreenColor);

	m_dir = Math::Vector3::Right;
	m_pos += m_dir*m_speed;
	if (m_pos.x > 10)
	{
		m_isExpired = true;
	}
}

void Fire::PostUpdate()
{
	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(0);
	m_mWorld = scaleMat * rotMatX * transMat;
}

void Fire::OnHit()
{
	m_isExpired = true;
}
