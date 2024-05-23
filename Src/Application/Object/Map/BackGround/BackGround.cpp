#include "BackGround.h"

void BackGround::Init()
{
	//m_model.Load("Asset/Models/Map/BackGround/background.gltf");
	m_pos = {0,0,40};
	m_scale = { 3 };
	m_rot = {};
}

void BackGround::DrawLit()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(270));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat* rotMat* transMat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
}
