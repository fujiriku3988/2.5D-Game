﻿#include "Warp.h"

void Warp::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Map/Warp/Warp.gltf");
	m_pos = {};
	m_scale = { 1.0f };
	m_rot = {};

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);
	m_objType = eStage;
}

void Warp::Update()
{
}

void Warp::DrawLit()
{
}

void Warp::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Warp::DrawBright()
{
}
