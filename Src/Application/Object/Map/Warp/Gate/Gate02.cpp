#include "Gate02.h"
#include"../../../../Object/Character/Player/Player.h"


void Gate02::Init()
{
	BaseGate::Init();
	m_pos = { 8.f,5.5f,-3.1f };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("gate02", { 0,0.5f,0.0f }, 0.2f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGate01;
}

void Gate02::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0.0f }, 0.3f, kGreenColor);
}

void Gate02::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, 0.5f);
	m_player.lock()->SetPos({ 12.0f,5.5f,6.0f });
}
