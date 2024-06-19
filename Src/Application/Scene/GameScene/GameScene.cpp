#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Map/Tile/Tile.h"
#include"../../Object/Map/BackGround/BackGround.h"
#include"../../Object/Map/Stage/Stage.h"
#include"../../Object/Map/Tree/Tree.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/Character/Enemy01/Enemy01.h"
#include"../../Object/Map/Ladder/Ladder.h"
#include"../../Object/Map/River/River.h"
#include"../../Object/Character/Enemy02/Enemy02.h"
#include"../../Object/Map/Goal/Goal.h"
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
	//カメラ操作
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_camRot.y -= 0.05f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_camRot.y += 0.05f; }

	//カメラの前ベクトル
	Math::Vector3 cameraVec;
	cameraVec = m_camera->GetCameraMatrix().Backward();

	//プレイヤーに情報を渡す
	Math::Vector3 playerPos;
	if (m_player.expired() == false) 
	{ 
		playerPos = m_player.lock()->GetPos();
		//カメラの角度をリセット
		if (GetAsyncKeyState('R') & 0x8000)
		{
			m_camRot = {};
			m_player.lock()->ResetRot();
		}
	}

	//テスト
	/*Math::Vector3 a = m_camera->GetCameraMatrix().Right();
	Math::Vector3 b = m_camera->GetCameraMatrix().Up();
	m_camRot *= b;*/

	//プレイヤーの移動行列
	Math::Matrix playerMat = Math::Matrix::CreateTranslation(playerPos);
	//行列の更新
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
	m_camPos = { 0.0f,2.5f,-10.0f };
	m_camRot = {};
	m_camRad = 0.0f;

	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.001f);
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0, -1, 10);

	//マップ関係
	shared_ptr<Tile>tile = make_shared<Tile>();
	tile->Init();
	AddObject(tile);

	shared_ptr<BackGround>back = make_shared<BackGround>();
	back->Init();
	AddObject(back);

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

	shared_ptr<Goal>goal = make_shared<Goal>();
	goal->Init();
	AddObject(goal);
	
	//キャラクター
	shared_ptr<Enemy01>enemy01 = make_shared<Enemy01>();
	enemy01->Init();
	AddObject(enemy01);

	shared_ptr<Enemy02>enemy02 = make_shared<Enemy02>();
	enemy02->Init();
	AddObject(enemy02);

	shared_ptr<Player>player = make_shared<Player>();
	player->Init();
	//player->SetCamera(m_camera);
	AddObject(player);
	m_player = player;
}
