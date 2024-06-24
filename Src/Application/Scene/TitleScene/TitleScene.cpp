#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"
#include"../../Object/Map/BackGround/BackGround02.h"
#include"../../Object/Character/Player/TitlePlayer.h"
#include"../../Object/Camera/Camera.h"
#include"../../Scene/Text/Title.h"
#include"../../Scene/Text/Click.h"

using namespace std;

void TitleScene::Event()
{
	ShowCursor(false);
	//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!m_keyFlg)
		{

			
			if (m_player.expired() == false)
			{
				m_player.lock()->AnimeOn();
			}
			if (m_click.expired() == false)
			{
				if (!m_click.lock()->GetClickFlg())
				{
					KdAudioManager::Instance().Play("Asset/Sounds/SE/click.wav", false, m_vol.click);
				}
				m_click.lock()->ClickOn();
			}
			m_keyFlg = true;
		}
		
	}
	else
	{
		m_keyFlg = false;
	}
	
}

void TitleScene::Init()
{
	m_vol.click = 0.3f;
	m_vol.BGM = 0.05f;

	KdAudioManager::Instance().StopAllSound();
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/bgm03.wav", true, m_vol.BGM);

	shared_ptr<BackGround02>back02 = make_shared<BackGround02>();
	back02->Init();
	AddObject(back02);

	shared_ptr<Title>title = make_shared<Title>();
	title->Init();
	AddObject(title);

	shared_ptr<Click>click = make_shared<Click>();
	click->Init();
	m_click = click;
	AddObject(click);

	shared_ptr<TitlePlayer>player = make_shared<TitlePlayer>();
	player->Init();
	m_player = player;
	AddObject(player);
}
