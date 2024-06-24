#include "TitlePlayer.h"

void TitlePlayer::Init()
{
	CharacterBase::Init();
	//m_poly = std::make_shared<KdSquarePolygon>();
	//m_poly->SetMaterial("Asset/Textures/obj/player/player1.png");
	m_tex.Load("Asset/Textures/obj/player/player3.png");
	m_pos = { 0,0,0 };
	m_spritePos = { 0,-200 };
	m_texSize = { 47,49 };
	m_dir = {};
	m_scale = { 5.0 };
	m_speed = 0.0f;
	m_dirType = DirType::Up;
	m_anime.speed = 0.05f;
	m_anime.count = 0;
	m_animeCnt = 1;
	m_color = { 1,1,1,1 };
	m_objType = KdGameObject::ePlayer;
	m_animeFlg = false;
}

void TitlePlayer::Update()
{
	if (m_animeFlg)
	{
		m_dir.y = 1.0f;
		//アニメーション情報
		m_anime.count += m_anime.speed;
		m_animeCnt = m_anime.count;

		Walk_U[m_animeCnt];

		if (m_animeCnt > 3)
		{
			m_anime.count = 0;
		}

		if (m_scale.x <= 0.0f) { m_scale.x = 0.0f; }
		if (m_scale.y <= 0.0f) { m_scale.y = 0.0f; }

		//プレイヤー情報
		m_speed = 0.5f;
		m_dir.Normalize();
		m_dir *= m_speed;
		m_spritePos.y += m_dir.y;
		m_scale.x += -0.01f;
		m_scale.y += -0.01f;
	}
}

void TitlePlayer::PostUpdate()
{
}

void TitlePlayer::DrawSprite()
{
	m_rect = { 47* Walk_U[m_animeCnt],49 * 3,47,49 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_spritePos.x, m_spritePos.y,
														m_texSize.x * m_scale.x, m_texSize.y * m_scale.y,
														&m_rect, &m_color);
}
