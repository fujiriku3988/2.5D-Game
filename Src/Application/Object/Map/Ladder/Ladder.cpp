#include "Ladder.h"

void Ladder::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Map/Ladder/Ladder2.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_rot = {};
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("LadderCollison", m_model, KdCollider::TypeEvent);
	m_objType = KdGameObject::eLadder;
}

void Ladder::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Ladder::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
