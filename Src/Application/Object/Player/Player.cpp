#include "Player.h"

void Player::Init()
{
	//m_poly = std::make_shared<KdSquarePolygon>();
	m_poly.SetMaterial("Asset/Textures/obj/player/player1.png");
	//m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = { 0,250,0 };
	m_scale = { 200 };
	m_poly.SetSplit(3, 4);
	m_anima = 0;
	m_poly.SetUVRect(1);
	Walk_Rflg = false;
	Walk_Lflg = false;
	Walk_Uflg = false;
	Walk_Dflg = false;
}

void Player::PreUpdate()
{
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_poly.SetUVRect(Walk_L[(int)m_anima]);
		Walk_Rflg = false;
		Walk_Lflg = true;
		Walk_Uflg = false;
		Walk_Dflg = false;
	}


	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_poly.SetUVRect(Walk_R[(int)m_anima]);
		Walk_Rflg = true;
		Walk_Lflg = false;
		Walk_Uflg = false;
		Walk_Dflg = false;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_poly.SetUVRect(Walk_U[(int)m_anima]);
		Walk_Rflg = false;
		Walk_Lflg = false;
		Walk_Uflg = true;
		Walk_Dflg = false;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_poly.SetUVRect(Walk_D[(int)m_anima]);
		Walk_Rflg = false;
		Walk_Lflg = false;
		Walk_Uflg = false;
		Walk_Dflg = true;
	}
	if (m_move.x == 0)
	{

		if (Walk_Lflg)
		{
			m_poly.SetUVRect(4);
			m_anima = 0;
		}
		if (Walk_Rflg)
		{
			m_poly.SetUVRect(7);
			m_anima = 0;
		}
	}
	if (m_move.z == 0)
	{
		if (Walk_Uflg)
		{
			m_poly.SetUVRect(10);
			m_anima = 0;
		}
		if (Walk_Dflg)
		{
			m_poly.SetUVRect(1);
			m_anima = 0;
		}
	}
}

void Player::Update()
{
	m_pos += m_move;
	m_move = { 0,0,0 };

	//プレイヤー動き
	if (GetAsyncKeyState('A') & 0x8000)
	{
		//m_move.x -= 0.1f;
		m_move.x -= 1.0f;
		m_anima += 0.08;
		if (m_anima >= 4)
		{
			m_anima = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		//m_move.x += 0.1f;
		m_move.x += 1.0f;
		m_anima += 0.08;
		if (m_anima >= 4)
		{
			m_anima = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.z += 1.0f;
		m_anima += 0.08;
		if (m_anima >= 4)
		{
			m_anima = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.z -= 1.0f;
		m_anima += 0.08;
		if (m_anima >= 4)
		{
			m_anima = 0;
		}
	}


	//m_poly.SetUVRect();

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Player::DrawLit()
{
}

void Player::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

void Player::DrawBright()
{
}
