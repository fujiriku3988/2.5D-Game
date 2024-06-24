#include "Fade.h"

#include"../Scene/SceneManager.h"

void Fade::Update()
{
	if (m_bColor)UpdateWhiteFade();
	else if (!m_bColor)UpdateBlackFade();
}

void Fade::Draw()
{
	if (m_bColor)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_whiteTex, 0, 0, nullptr, &m_whiteColor);
	}
	else if (!m_bColor)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_blackTex, 0, 0, nullptr, &m_blackColor);
	}
}

//ステージ切り替えやシーン切り替えに使おうかな
void Fade::UpdateBlackFade()
{
	if (m_bFadeOut)
	{
		m_blackAlpha += 0.008f;
		if (m_blackAlpha >= 1.0f)
		{
			m_bFadeOut = false;
			m_blackAlpha = 1.0f;
			SceneManager::Instance().SetNextScene(m_nextScene);
			m_bFadeIn = true;
		}
		m_blackColor = { 1.0f,1.0f,1.0f,m_blackAlpha };
	}

	if (m_bFadeIn)
	{
		m_blackAlpha -= 0.008f;
		if (m_blackAlpha <= 0.0f)
		{
			m_bFadeIn = false;
			m_blackAlpha = 0.0f;
			SceneManager::Instance().SetNextScene(m_nextScene);
			m_bFade = false;
		}
		m_blackColor = { 1.0f,1.0f,1.0f,m_blackAlpha };
	}
}

void Fade::UpdateWhiteFade()
{
	if (m_bFadeOut)
	{
		m_whiteAlpha += 0.008f;
		if (m_whiteAlpha >= 1.0f)
		{
			m_bFadeOut = false;
			m_whiteAlpha = 1.0f;
			SceneManager::Instance().SetNextScene(m_nextScene);
			m_bFadeIn = true;
		}
		m_whiteColor = { 1.0f,1.0f,1.0f,m_whiteAlpha };
	}

	if (m_bFadeIn)
	{
		m_whiteAlpha -= 0.008f;
		if (m_whiteAlpha <= 0.0f)
		{
			m_bFadeIn = false;
			m_whiteAlpha = 0.0f;
			m_bFade = false;
		}
		m_whiteColor = { 1.0f,1.0f,1.0f,m_whiteAlpha };
	}
}

void Fade::BootBlackFade(SceneManager::SceneType _type)
{
	m_bFade = true;
	m_bFadeOut = true;
	m_nextScene = _type;
	m_bColor = false;
}

void Fade::BootWhiteFade(SceneManager::SceneType _type)
{
	m_bFade = true;
	m_bFadeOut = true;
	m_nextScene = _type;
	m_bColor = true;
}

void Fade::Init()
{
	m_bFade = false;
	m_bFadeOut = false;
	m_bFadeIn = false;
	m_bColor = false;

	m_blackTex.Load("Asset/Textures/Fade/black.png");
	m_blackMat = Math::Matrix::Identity;
	m_blackAlpha = 0.0f;
	m_blackColor = { 1.0f,1.0f,1.0f,m_blackAlpha };
	
	m_whiteTex.Load("Asset/Textures/Others/white.png");
	m_whiteMat = Math::Matrix::Identity;
	m_whiteAlpha = 0.0f;
	m_whiteColor = { 1.0f,1.0f,1.0f,m_whiteAlpha };
}
