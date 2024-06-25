#include "Fire.h"

void Fire::Init()
{
	BaseEffect::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy01/fire01.png");
	m_pos = {};
	m_scale = { 1 };
	m_speed = 0.05f;
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_dissolve = 0;
	m_dissolveMAX = 1.0f;
	m_dissolveSpeed = 0.01f;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("fire", { 0,0.5f,0 }, 0.3f, KdCollider::TypeDamage);
	m_objType = KdGameObject::eFireAttack;
}

void Fire::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Fire::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos+Math::Vector3{0,0.5f,0}, 0.3f, kGreenColor);

	m_dissolve += m_dissolveSpeed;
	if (m_dissolve > m_dissolveMAX)
	{
		m_dissolve = m_dissolveMAX;
	}
	if (m_dissolve == m_dissolveMAX)
	{
		m_isExpired = true;
	}

	m_dir = Math::Vector3::Right;
	m_pos += m_dir*m_speed;
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
