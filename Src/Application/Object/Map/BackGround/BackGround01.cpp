#include "BackGround01.h"

void BackGround01::Init()
{
	m_model.Load("Asset/Models/Map/BackGround/background.gltf");//空
	m_pos = { 0,0,200 };
	m_scale = { 30 };
	m_rot = {};
	m_color = { 3,3,3,0.9 };
}

void BackGround01::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(270));
	Math::Matrix rotMatY = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld, m_color);
}
