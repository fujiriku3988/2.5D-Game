#include "BackGround.h"

void BackGround::Init()
{
	m_model.Load("Asset/Models/Map/BackGround/background.gltf");
	m_pos = { 0,0,200 };
	m_scale = { 30 };
	m_rot = {};
}

void BackGround::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(270));
	Math::Matrix rotMatY = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * rotMatY * rotMatX * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
}
