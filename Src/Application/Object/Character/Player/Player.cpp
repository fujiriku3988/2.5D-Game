#include "Player.h"
#include"../../../Scene/SceneManager.h"

void Player::Init()
{
	CharacterBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/player/player1.png");
	m_pos = { 0,10,0 };
	m_scale = { 1.0 };
	m_speed = 0.05f;
	m_poly->SetSplit(3, 4);
	m_anime = 0;
	m_animeSpeed = 0.08f;
	m_poly->SetUVRect(1);
	Walk_Rflg = false;
	Walk_Lflg = false;
	Walk_Uflg = false;
	Walk_Dflg = false;
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void Player::PreUpdate()
{
	// 前方向ベクトル
	m_playerFowardVec = GetMatrix().Backward();
	m_playerSideVec = GetMatrix().Right();
	//m_playerFowardVec = m_camVec;
	//camera.GetMatrix().Backward();

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_poly->SetUVRect(Walk_L[(int)m_anime]);
		Walk_Rflg = false;
		Walk_Lflg = true;
		Walk_Uflg = false;
		Walk_Dflg = false;
	}


	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_poly->SetUVRect(Walk_R[(int)m_anime]);
		Walk_Rflg = true;
		Walk_Lflg = false;
		Walk_Uflg = false;
		Walk_Dflg = false;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_poly->SetUVRect(Walk_U[(int)m_anime]);
		Walk_Rflg = false;
		Walk_Lflg = false;
		Walk_Uflg = true;
		Walk_Dflg = false;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_poly->SetUVRect(Walk_D[(int)m_anime]);
		Walk_Rflg = false;
		Walk_Lflg = false;
		Walk_Uflg = false;
		Walk_Dflg = true;
	}
	if (m_move.x == 0)
	{

		if (Walk_Lflg)
		{
			m_poly->SetUVRect(4);
			m_anime = 0;
		}
		if (Walk_Rflg)
		{
			m_poly->SetUVRect(7);
			m_anime = 0;
		}
	}
	if (m_move.z == 0)
	{
		if (Walk_Uflg)
		{
			m_poly->SetUVRect(10);
			m_anime = 0;
		}
		if (Walk_Dflg)
		{
			m_poly->SetUVRect(1);
			m_anime = 0;
		}
	}
	
}

void Player::Update()
{
	//m_dir = m_camPos - m_pos;
	//m_dir.Normalize();
	//m_pos += m_move * m_dir;
	//m_move *=m_playerVec;
	m_pos += m_move;
	m_move = { 0,0,0 };

	//プレイヤー動き
	if (GetAsyncKeyState('A') & 0x8000)
	{
		//m_move.x -= 0.1f;
		//m_move.x -= m_speed;
		m_move += m_playerSideVec * -m_speed;
		m_anime += m_animeSpeed;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		//m_move.x += 0.1f;
		//m_move.x += m_speed;
		m_move += m_playerSideVec * m_speed;
		m_anime += m_animeSpeed;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		//m_move.z += m_speed;
		m_move += m_playerFowardVec * m_speed;
		m_anime += m_animeSpeed;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		//m_move.z += -m_speed;
		m_move += m_playerFowardVec * -m_speed;
		m_anime += m_animeSpeed;
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_rot.y -= 0.05f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_rot.y += 0.05f; }
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_rot.x += 0.05f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_rot.x -= 0.05f; }

	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

}

void Player::PostUpdate()
{
	KdCollider::RayInfo ray;
	ray.m_pos = m_pos;
	ray.m_dir = Math::Vector3::Down;
	ray.m_pos.y += -0.05f;

	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	ray.m_range = m_gravity + enableStepHigh;

	ray.m_type = KdCollider::TypeGround;

	std::list<KdCollider::CollisionResult>retRayList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	//デバッグ（レイ可視化）
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	float maxOverLap = 0;	//はみ出たレイの長さ
	Math::Vector3 hitPos;	//レイが遮断された座標（当たった座標）
	bool ishit = false;		//当たっていたらTrue
	//Math::Vector3 a = { 0,0.5,0 };
	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			ishit = true;
		}
	}
	if (ishit)
	{
		//当たっている
		m_pos = hitPos + Math::Vector3{ 0,0.0f,0 };
		m_gravity = 0;
	}

	////////////////////////////////////
	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;//スフィア
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3{ 0,0.5,0 };
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
	//球が当たったオブジェクトの情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}
	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;		//はみ出た例の長さ
	Math::Vector3 hitDir = {};		//レイが遮断された方向（当たった方向）
	ishit = false;			//当たっていたらレイ
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;//当たった方向
			ishit = true;
		}

	}
	if (ishit)
	{
		//z方向無効
		//hitDir.z = 0;

		//方向ベクトルは長さ１にする必要がある 
		hitDir.Normalize();
		//押し戻し
		m_pos += hitDir * maxOverLap;
	}

	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(m_rot.x);
	rotMatY = Math::Matrix::CreateRotationY(m_rot.y);
	rotMatZ = Math::Matrix::CreateRotationZ(m_rot.z);
	m_mWorld = scaleMat * rotMatY * transMat;
}

