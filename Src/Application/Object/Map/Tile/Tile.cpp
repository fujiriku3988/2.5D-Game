#include "Tile.h"

void Tile::Init()
{
	//m_model.Load("Asset/Models/Map/MapTile/tile.gltf");
	m_pos = {};
	m_scale = { 10 };
	m_rot = {};
}

void Tile::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model,m_mWorld);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = scaleMat;
}
