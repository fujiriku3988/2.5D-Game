#include "Goal.h"

void Goal::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/goal/aura01.png");
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = { 14,4.f,10.8 };
	m_scale = { 4.0f };
	m_rot = {};
	m_poly->SetSplit(8, 4);
	m_poly->SetUVRect(0);
	m_color = { 1,1,1,1 };
	m_alphaMAX = 1.5f;
	m_alpha = m_alphaMAX;
	m_alphaMIN = 0.5f;
	m_alSpeed = 0.01f;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Goal", { 0,0.5f,0.0f }, 0.1f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGoal;
}

void Goal::Update()
{
	m_alpha += -m_alSpeed;
	if (m_alpha < m_alphaMIN)
	{
		m_alSpeed *= -1;
	}
	if (m_alpha > m_alphaMAX)
	{
		m_alSpeed *= -1;
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Goal::DrawLit()
{
	m_color = { 10,10,10,m_alpha };
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
}
