#include "Gate01.h"
#include"../../../../Object/Character/Player/Player.h"

void Gate01::Init()
{
	BaseGate::Init();
	m_pos = { 14.f,3.5f,3.f };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("gate01", { 0,0.5f,0.0f }, 0.2f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGate01;
	m_vol = 0.5f;
}

void Gate01::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0.0f }, 0.3f, kGreenColor);
}

void Gate01::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, m_vol);
	m_player.lock()->SetPos({ 8.0f,6.0f,0 });
}
