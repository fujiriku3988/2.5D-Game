#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Map/Tile/Tile.h"
#include"../../Object/Map/BackGround/BackGround.h"
#include"../../Object/Map/Stage/Stage.h"
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
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_camRot.y += 0.1f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_camRot.y -= 0.1f; }
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_camRad += 1.0f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_camRad -= 1.0f; }
	/*if (GetAsyncKeyState(VK_UP) & 0x8000) { m_camRad += 1.0f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_camRad -= 1.0f; }*/
	if (GetAsyncKeyState('A') & 0x8000) { m_camPos.x -= 10.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_camPos.x += 10.0f; }
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_camRot = {};
	}


	
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_camPos);
	Math::Matrix rotMatY = Math::Matrix::CreateRotationY(m_camRot.y);
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(m_camRot.x);
	Math::Matrix camX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_camRad));
	Math::Matrix Matrix = camX*transMat * rotMatY* rotMatX;
	m_camera->SetCameraMatrix(Matrix);

}

void GameScene::Init()
{
	m_camera = make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(90);
	m_camPos = { 0.0f,200.0f,-400.0f };
	m_camRot = {};
	m_camRad = 20.0f;
	

	shared_ptr<Tile>tile = make_shared<Tile>();
	tile->Init();
	AddObject(tile);

	shared_ptr<BackGround>back = make_shared<BackGround>();
	back->Init();
	AddObject(back);

	shared_ptr<Stage>stage = make_shared<Stage>();
	stage->Init();
	AddObject(stage);
}
