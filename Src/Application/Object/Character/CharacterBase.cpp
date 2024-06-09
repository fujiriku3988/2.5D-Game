﻿#include "CharacterBase.h"

void CharacterBase::Init()
{
	m_pos = { };
	m_scale = { 1 };
	m_move = {};
	m_poly = nullptr;
	m_model = nullptr;
	scaleMat = Math::Matrix::Identity;
	transMat = Math::Matrix::Identity;
	rotationMat = Math::Matrix::Identity;
	m_gravity = 0;
	m_anima = 0;
	m_speed = 0;
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void CharacterBase::PreUpdate()
{
}

void CharacterBase::Update()
{
}

void CharacterBase::PostUpdate()
{
}

void CharacterBase::DrawLit()
{
	if (m_model)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}

void CharacterBase::GenerateDepthMapFromLight()
{
	if (m_model)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
	}
}
