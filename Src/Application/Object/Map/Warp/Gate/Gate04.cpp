#include "Gate04.h"
#include"../../../../Object/Character/Player/Player.h"

void Gate04::Init()
{
	BaseGate::Init();
	m_pos = { 14.f,3.5f,-3.1f };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("gate04", { 0,0.5f,0.0f }, 0.2f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGate04;
	m_vol = 0.5f;
}

void Gate04::Update()
{
}

void Gate04::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, m_vol);
	m_player.lock()->SetPos({ 8.0f, 5.5f, 4.0f });
}
