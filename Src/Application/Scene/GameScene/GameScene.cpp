#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Map/Tile/Tile.h"
#include"../../Object/Map/BackGround/BackGround.h"
#include"../../Object/Map/Stage/Stage.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/Character/Enemy01/Enemy01.h"
using namespace std;

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_camRot.y -= 0.05f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_camRot.y += 0.05f; }
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_camRot.x += 0.05f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_camRot.x -= 0.05f; }
	/*if (GetAsyncKeyState(VK_UP) & 0x8000) { m_camRad -= 1.0f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_camRad += 1.0f; }*/
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_camRot = {};
	}

	Math::Vector3 playerPos;
	if (m_player.expired() == false) 
	{ 
		playerPos = m_player.lock()->GetPos();
		m_player.lock()->SetCameraPos(m_camPos);
	}
	Math::Matrix playerMat = Math::Matrix::CreateTranslation(playerPos);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_camPos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(m_camRot.y);
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(m_camRot.x);
	Math::Matrix camX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_camRad));
	Math::Matrix Matrix = camX * transMat * rotMatY * rotMatX * playerMat;
	m_camera->SetCameraMatrix(Matrix);

}

void GameScene::Init()
{
	m_camera = make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);
	m_camPos = { 0.0f,2.0f,-7.0f };
	m_camRot = {};
	m_camRad = 0.0f;


	shared_ptr<Tile>tile = make_shared<Tile>();
	tile->Init();
	AddObject(tile);

	shared_ptr<BackGround>back = make_shared<BackGround>();
	back->Init();
	AddObject(back);

	shared_ptr<Stage>stage = make_shared<Stage>();
	stage->Init();
	AddObject(stage);
	
	shared_ptr<Enemy01>enemy01 = make_shared<Enemy01>();
	enemy01->Init();
	AddObject(enemy01);

	shared_ptr<Player>player = make_shared<Player>();
	player->Init();
	AddObject(player);
	m_player = player;
}
