#include "Goal.h"

void Goal::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/goal/aura01.png");
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = {-2,4.5f,0};
	m_scale = { 2.0f };
	m_rot = {};
	m_poly->SetSplit(8, 4);
	m_poly->SetUVRect(0);

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("GoalCollision", m_poly, KdCollider::TypeGround);
}

void Goal::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Goal::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Goal::DrawBright()
{
}
