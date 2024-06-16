#include "Tree.h"

void Tree::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Map/Tree/tree4.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_rot = {};

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("TreeCollison", m_model, KdCollider::TypeGround);
}

void Tree::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Tree::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Tree::DrawUnLit()
{
}

void Tree::DrawBright()
{
}
