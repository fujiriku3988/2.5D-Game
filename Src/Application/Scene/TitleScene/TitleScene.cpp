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
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_keyFlg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/click.wav",false,0.3f);
			if (m_player.expired() == false)
			{
				m_player.lock()->AnimeOn();
			}
			if (m_click.expired() == false)
			{
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
	KdAudioManager::Instance().StopAllSound();
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/bgm03.wav", true, 0.05f);

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
