#include "BaseGate.h"

void BaseGate::Init()
{
	m_pos = { };
	m_scale = { 2 };
	m_move = {};
	m_poly = nullptr;
	m_color = { 1,3,1,1 };
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/warp/warpgate.png");
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_poly->SetSplit(4, 4);
	m_poly->SetUVRect(0);
	scaleMat = Math::Matrix::Identity;
	transMat = Math::Matrix::Identity;
	rotMatX = Math::Matrix::Identity;
	rotMatY = Math::Matrix::Identity;
	rotMatZ = Math::Matrix::Identity;
	m_anime = 0;
	m_animeSpeed = 0.2f;
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void BaseGate::PreUpdate()
{
	m_anime += m_animeSpeed;
	m_poly->SetUVRect(m_warp[(int)m_anime]);
	if (m_anime > 15)
	{
		m_anime = 0;
	}
}

void BaseGate::Update()
{
	
}

void BaseGate::PostUpdate()
{
	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatX * transMat;
}

void BaseGate::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld, m_color);
}

void BaseGate::OnHit()
{
	
}

