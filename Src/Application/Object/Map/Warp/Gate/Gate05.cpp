#include "Gate05.h"
#include"../../../../Object/Character/Player/Player.h"

void Gate05::Init()
{
	BaseGate::Init();
	m_pos = { 12.f,5.5f,3.1f };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("gate05", { 0,0.5f,0.0f }, 0.2f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGate05;
	m_vol = 0.5f;
}

void Gate05::Update()
{
}

void Gate05::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, m_vol);
	m_player.lock()->SetPos({ 13.5f,4.0f,2.0f });
}
