#include "Player.h"
#include"../../../Scene/SceneManager.h"

void Player::Init()
{
	CharacterBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/player/player1.png");
	m_pos = { 0,6,3 };
	m_dir = {};
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
	m_hitFlg = false;
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_color = { 1,1,1,1 };
	m_time = 6;
	m_objType = KdGameObject::ePlayer;
	m_tex.Load("Asset/Textures/obj/player/hp03.png");
	m_maxHp = 3;
	m_nowHp = m_maxHp;
	m_color = { 1,1,1,1 };
}

void Player::PreUpdate()
{
	if (m_nowHp <= 0)
	{
		m_nowHp = 0;
		if (m_nowHp == 0)
		{
			//m_isExpired = true;
		}
	}
	// 前方向ベクトル
	m_playerFowardVec = GetMatrix().Backward();//後ろ向き
	m_playerSideVec = GetMatrix().Right();//右向き

	//キャラアニメーション
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

	//ダメージ受けた時のカラー変更
	if (m_hitFlg)
	{
		m_time--;
		if (m_time >= 0)
		{
			m_color = { 10,10,10,1 };
		}
		else
		{
			m_hitFlg = false;
			m_time = 6;
		}

	}
	else
	{
		m_color = { 1,1,1,1 };
	}

}

void Player::Update()
{
	m_pos += m_move;
	m_move = { 0,0,0 };
	m_pos.y += -m_gravity;
	m_gravity += 0.003f;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.05f;
	}

	//プレイヤー動き
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move += m_playerSideVec * -m_speed;
		m_anime += m_animeSpeed;
		m_dir = GetMatrix().Left();
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move += m_playerSideVec * m_speed;
		m_anime += m_animeSpeed;
		m_dir = GetMatrix().Right();
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move += m_playerFowardVec * m_speed;
		m_anime += m_animeSpeed;
		m_dir = GetMatrix().Forward();
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move += m_playerFowardVec * -m_speed;
		m_anime += m_animeSpeed;
		m_dir = GetMatrix().Backward();
		if (m_anime >= 4)
		{
			m_anime = 0;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_rot.y -= 0.05f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_rot.y += 0.05f; }

}

void Player::PostUpdate()
{
	if (m_pos.y < -20)
	{
		OnHit();
		m_pos = { 0,6,3 };
	}

	//レイ飛ばして当たり判定
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
	sphere.m_type = KdCollider::TypeGround | KdCollider::TypeDamage;
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
	//球が当たったオブジェクトの情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			if (obj->GetObjType() == KdGameObject::eFireAttack)
			{
				obj->OnHit();
				OnHit();
			}
			if (obj->GetObjType() == KdGameObject::eEnemy)
			{
				OnHit();
			}
		}
	}
	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;
	Math::Vector3 hitDir = {};
	ishit = false;
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
		//方向ベクトルは長さ１にする必要がある 
		hitDir.Normalize();
		//押し戻し
		m_pos += hitDir * maxOverLap;
	}

	////////////////////////////////////
	//球判定用の変数を作成
	KdCollider::SphereInfo sphere2;//スフィア
	//球の中心位置を設定
	sphere2.m_sphere.Center = m_pos + Math::Vector3{ 0,0.5,0 };
	//球の半径を設定
	sphere2.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere2.m_type = KdCollider::TypeEvent;
	m_pDebugWire->AddDebugSphere(sphere2.m_sphere.Center, sphere2.m_sphere.Radius);
	//球が当たったオブジェクトの情報を格納するリスト
	//std::list<KdCollider::CollisionResult> retSphereList;
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere2, &retSphereList))
		{
			if (obj->GetObjType() == KdGameObject::eLadder)
			{
				//obj->OnHit();
				OnHitLadder();
			}
		}
	}
	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;
	hitDir = {};
	ishit = false;
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
		//方向ベクトルは長さ１にする必要がある 
		//hitDir.Normalize();
		//押し戻し
		//m_pos += hitDir * maxOverLap;
		//OnHitLadder();
	}

	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(m_rot.x);
	rotMatY = Math::Matrix::CreateRotationY(m_rot.y);
	rotMatZ = Math::Matrix::CreateRotationZ(m_rot.z);
	m_mWorld = scaleMat * rotMatY * transMat;
}

void Player::DrawSprite()
{
	m_rect = { 0,0,32 * m_nowHp,32 };
	m_color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y, 32 * m_nowHp, 32, &m_rect, &m_color);
}

void Player::OnHit()
{
	m_hitFlg = true;
	m_nowHp--;
	Math::Vector3 a = GetMatrix().Forward();
	Math::Vector3 b = GetMatrix().Backward();
	//m_pos += m_playerFowardVec * 2;
	m_pos += m_dir * 1.5;
}

void Player::OnHitLadder()
{
	m_gravity = -0.05f;
}
