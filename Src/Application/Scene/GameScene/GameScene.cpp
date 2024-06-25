#include"../../main.h"
#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Map/BackGround/BackGround01.h"
#include"../../Object/Map/Stage/Stage.h"
#include"../../Object/Map/Tree/Tree.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/Character/Enemy01/Enemy01.h"
#include"../../Object/Map/Ladder/Ladder.h"
#include"../../Object/Map/River/River.h"
#include"../../Object/Character/Enemy02/Enemy02.h"
#include"../../Object/Map/Goal/Goal.h"
#include"../../Object/Map/Warp/Warp.h"
#include"../../Object/Map/Warp/gate/Gate01.h"
#include"../../Object/Map/Warp/gate/Gate02.h"
#include"../../Object/Map/Warp/gate/Gate03.h"
#include"../../Object/Map/Warp/gate/Gate04.h"
#include"../../Object/Map/Warp/gate/Gate05.h"
#include"../../Object/Camera/Camera.h"
#include"../../Scene/Text/GameOver.h"
#include"../../Scene/Text/GameClear.h"
using namespace std;

void GameScene::Event()
{
	ShowCursor(false);
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	if (m_player.expired() == false)
	{
		if (!m_player.lock()->GetAliveFlg())
		{
			std::shared_ptr<GameOver>over = std::make_shared<GameOver>();
			over->Init();
			AddObject(over);
		}
	}
	if (m_player.lock()->GetGoalFlg())
	{
		std::shared_ptr<GameClear>clear = std::make_shared<GameClear>();
		clear->Init();
		AddObject(clear);
	}
}

void GameScene::Init()
{

	shared_ptr<Player>player = make_shared<Player>();
	player->Init();

	{
		//マップ関係
		shared_ptr<BackGround01>back01 = make_shared<BackGround01>();
		back01->Init();
		AddObject(back01);

		shared_ptr<Stage>stage = make_shared<Stage>();
		stage->Init();
		AddObject(stage);

		shared_ptr<Tree>tree = make_shared<Tree>();
		tree->Init();
		AddObject(tree);

		shared_ptr<River>river = make_shared<River>();
		river->Init();
		AddObject(river);

		shared_ptr<Ladder>laddrer = make_shared<Ladder>();
		laddrer->Init();
		AddObject(laddrer);

		shared_ptr<Warp>warp = make_shared<Warp>();
		warp->Init();
		AddObject(warp);

		shared_ptr<Gate01>gate01 = make_shared<Gate01>();
		gate01->Init();
		gate01->SetPlayer(player);
		AddObject(gate01);

		shared_ptr<Gate02>gate02 = make_shared<Gate02>();
		gate02->Init();
		gate02->SetPlayer(player);
		AddObject(gate02);

		shared_ptr<Gate03>gate03 = make_shared<Gate03>();
		gate03->Init();
		gate03->SetPlayer(player);
		AddObject(gate03);

		shared_ptr<Gate04>gate04 = make_shared<Gate04>();
		gate04->Init();
		gate04->SetPlayer(player);
		AddObject(gate04);

		shared_ptr<Gate05>gate05 = make_shared<Gate05>();
		gate05->Init();
		gate05->SetPlayer(player);
		AddObject(gate05);


		shared_ptr<Goal>goal = make_shared<Goal>();
		goal->Init();
		AddObject(goal);
	}
	//キャラクター
	shared_ptr<Enemy01>enemy01 = make_shared<Enemy01>();
	enemy01->Init();
	enemy01->SetPos({ 1.1f,5,0.3f });
	AddObject(enemy01);
	//２体目
	enemy01 = make_shared<Enemy01>();
	enemy01->Init();
	enemy01->SetPos({ 7.5f,5.0f,7.3f });
	AddObject(enemy01);

	shared_ptr<Enemy02>enemy02 = make_shared<Enemy02>();
	enemy02->Init();
	enemy02->SetPos({ -1.0f,5.0f,7.0f });
	AddObject(enemy02);
	//２体目
	enemy02 = make_shared<Enemy02>();
	enemy02->Init();
	enemy02->SetPos({ -1.0f,5.0f,10.0f });
	AddObject(enemy02);

	//プレイヤー
	AddObject(player);

	shared_ptr<Camera>camera = make_shared<Camera>();
	camera->Init();
	camera->SetTarget(player);
	player->SetCamera(camera);
	AddObject(camera);
	m_player = player;
}
