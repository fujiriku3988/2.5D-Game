#include "BaseEffect.h"

void BaseEffect::Init()
{
	m_pos = { };
	m_scale = { 1 };
	m_move = {};
	m_poly = nullptr;
	m_color = { 1,1,1,1 };
	scaleMat = Math::Matrix::Identity;
	transMat = Math::Matrix::Identity;
	rotMatX = Math::Matrix::Identity;
	rotMatY = Math::Matrix::Identity;
	rotMatZ = Math::Matrix::Identity;
	m_anime = 0;
	m_speed = 0;
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void BaseEffect::PreUpdate()
{
}

void BaseEffect::Update()
{
}

void BaseEffect::PostUpdate()
{
}

void BaseEffect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
}

void BaseEffect::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
}
