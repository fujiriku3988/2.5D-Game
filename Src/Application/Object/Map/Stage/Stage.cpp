#include "Stage.h"

void Stage::Init()
{
	m_model.Load("Asset/Models/Map/Stage/stage3.gltf");
	m_pos = {};
	m_scale = { 100.0f };
	m_rot = {};
}

void Stage::Update()
{

}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Stage::DrawUnLit()
{

}

void Stage::DrawBright()
{

}
