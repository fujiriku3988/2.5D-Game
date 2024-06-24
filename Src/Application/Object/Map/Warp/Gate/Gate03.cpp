#include "Gate03.h"
#include"../../../../Object/Character/Player/Player.h"

void Gate03::Init()
{
	BaseGate::Init();
	m_pos = { 14.f,5.5f,-1.1f };
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("gate03", { 0,0.5f,0.0f }, 0.2f, KdCollider::TypeEvent);
	m_objType = KdGameObject::eGate03;
	m_vol = 0.5f;
}

void Gate03::Update()
{
}

void Gate03::OnHit()
{
	KdAudioManager::Instance().Play("Asset/Sounds/SE/warp.wav", false, m_vol);
	m_player.lock()->SetPos({ 13.5f,4.0f,2.0f });
}
