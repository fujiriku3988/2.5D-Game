#include "CharacterBase.h"

void CharacterBase::Init()
{
	m_pos = { };
	m_scale = { 1 };
	m_spritePos = {};
	m_poly = nullptr;
	m_model = nullptr;
	m_hitFlg = false;
	m_texSize = {};
	scaleMat = Math::Matrix::Identity;
	transMat = Math::Matrix::Identity;
	rotMatX = Math::Matrix::Identity;
	rotMatY = Math::Matrix::Identity;
	rotMatZ = Math::Matrix::Identity;
	m_gravity = 0.0f;
	m_speed = 0.0f;
	m_animeCnt = 0;
	m_animeCntMAX = 0;
	m_anime.count = 0;
	m_anime.speed = 0;
	m_vol.walk = 1.0f;
	m_vol.damage = 1.0f;
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
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld,m_color);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld,m_color);
	}
}

void CharacterBase::DrawSprite()
{
}

void CharacterBase::GenerateDepthMapFromLight()
{
	if (m_model)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, m_color);
	}
	if (m_poly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
	}
}
