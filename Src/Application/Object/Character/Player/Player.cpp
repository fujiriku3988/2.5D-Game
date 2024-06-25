#include "Player.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Object/Camera/Camera.h"
#include"../../../Fade/Fade.h"
#include"../../../Scene/Text/GameClear.h"
#include"../../../Scene/Text/GameOver.h"

void Player::Init()
{
	CharacterBase::Init();
	//プレイヤー
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/player/player1.png");
	m_poly->SetSplit(3, 4);
	m_poly->SetUVRect(1);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = { -3,3,-4 };
	m_dir = {};
	m_scale = { 1.0 };
	m_texSize = { 96,96 };
	m_speed = 0.05f;
	m_vol.damage = 0.5f;
	m_vol.walk = 0.3f;
	//アニメーション関係
	m_walkWait = 0;
	m_dirType = DirType::Down;
	m_anime.speed = 0.05f;
	m_anime.count = 0;
	m_animeCnt = 0;
	m_animeCntMAX = 3;
	m_color = { 1,1,1,1 };
	m_time = 6;//ダメージ表現時間
	m_timeFrame = m_time;
	m_objType = KdGameObject::ePlayer;
	//HP
	m_tex.Load("Asset/Textures/obj/player/hp04.png");
	m_maxHp = 3;
	m_nowHp = m_maxHp;
	m_color = { 1,1,1,1 };
	m_spritePos = { -620,330 };
	//フラグ関係
	m_hitFlg = false;//当たったか
	m_keyFlg = false;//キー押してるか
	m_walkFlg = false;//歩いているか
	m_aliveFlg = true;//生存
	m_goalFlg = false;//ゴールフラグ
}

void Player::PreUpdate()
{
	//HP
	if (m_nowHp <= 0)
	{
		m_nowHp = 0;
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
			m_time = m_timeFrame;
		}
	}
	else
	{
		m_color = { 1,1,1,1 };
	}
	m_keyFlg = false;
	m_walkFlg = false;
}

void Player::Update()
{
	m_playerFowardVec = GetMatrix().Forward();
	m_playerSideVec = GetMatrix().Right();
	m_speed = 0.05f;
	//後で消す
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.05f;
	}
	
	m_dir = Math::Vector3::Zero;
	if (m_nowHp >= 1 && !m_goalFlg)
	{
		//プレイヤー動き
		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_dirType |= Left;
			m_dir.x = -1.0f;
			m_keyFlg = true;
			m_walkFlg = true;
			m_poly->SetUVRect(Walk_L[(int)m_animeCnt]);
			m_vecDir = m_playerSideVec;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_dirType |= Right;
			m_dir.x = 1.0f;
			m_keyFlg = true;
			m_walkFlg = true;
			m_poly->SetUVRect(Walk_R[(int)m_animeCnt]);
			m_vecDir = -m_playerSideVec;
		}

		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_dirType |= Up;
			m_dir.z = 1.0f;
			m_keyFlg = true;
			m_walkFlg = true;
			m_poly->SetUVRect(Walk_U[(int)m_animeCnt]);
			m_vecDir = m_playerFowardVec;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_dirType |= Down;
			m_dir.z = -1.0f;
			m_keyFlg = true;
			m_walkFlg = true;
			m_poly->SetUVRect(Walk_D[(int)m_animeCnt]);
			m_vecDir = -m_playerFowardVec;
		}
	}

	if (m_walkFlg)
	{
		m_walkWait--;
		if (m_walkWait <= 0) { m_walkWait = 0; }
		if (m_walkWait == 0)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/walk.wav", false, m_vol.walk);
			m_walkWait = 40;
		}
	}

	//アニメーション情報
	m_anime.count += m_anime.speed;
	m_animeCnt = m_anime.count;

	if (m_animeCnt > m_animeCntMAX)
	{
		m_animeCnt = 0;
		m_anime.count = 0;
	}

	//カメラ計算
	std::shared_ptr<Camera> camera = m_wpCamera.lock();
	if (camera)
	{
		//カメラのベクトルを計算して
		//プレイヤーに合わせて補正してる
		m_dir = m_dir.TransformNormal(m_dir, camera->GetRotationYMatrix());
		//カメラが回転したらプレイヤーも回転
		rotMatY = camera->GetRotationYMatrix();
	}

	//ゲームオーバー処理
	if (m_nowHp == 0)
	{
		m_poly->SetUVRect(Walk_U[1]);
		m_rot.x = 80;
		rotMatY = Math::Matrix::CreateRotationY(0);
		m_pos.y = 3.2;
		m_gravity = 0;
		m_aliveFlg = false;
	}

	//プレイヤー情報
	m_dir.Normalize();
	m_dir *= m_speed;
	m_pos += m_dir;
	m_pos.y += -m_gravity;
	m_gravity += 0.003f;
}

void Player::PostUpdate()
{
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
	//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

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
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);
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
	//m_pDebugWire->AddDebugSphere(sphere2.m_sphere.Center, sphere2.m_sphere.Radius);
	//球と当たり判定！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere2, &retSphereList))
		{
			if (obj->GetObjType() == KdGameObject::eLadder)
			{ 
				OnHitLadder();
				m_walkWait = 40;
			}
			if (obj->GetObjType() == KdGameObject::eGoal) { OnHitGoal(); }
			if (obj->GetObjType() == KdGameObject::eGate01) { obj->OnHit(); }
			if (obj->GetObjType() == KdGameObject::eGate02) { obj->OnHit(); }
			if (obj->GetObjType() == KdGameObject::eGate03) { obj->OnHit(); }
			if (obj->GetObjType() == KdGameObject::eGate04) { obj->OnHit(); }
			if (obj->GetObjType() == KdGameObject::eGate05) { obj->OnHit(); }
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

	}

	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatX = Math::Matrix::CreateRotationX(m_rot.x);
	m_mWorld = scaleMat * rotMatY * rotMatX * transMat;
}

void Player::DrawSprite()
{
	m_rect = { 0,0,(long)m_texSize.x * m_nowHp,(long)m_texSize.y };
	m_color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_spritePos.x, m_spritePos.y, m_texSize.x * m_nowHp, m_texSize.y, &m_rect, &m_color, { 0.f,0.5f });
}

void Player::OnHit()
{
	m_hitFlg = true;
	m_nowHp--;
	m_pos += m_vecDir * 1.5;
	KdAudioManager::Instance().Play("Asset/Sounds/SE/damage.wav", false, m_vol.damage);
}

void Player::OnHitGoal()
{
	m_goalFlg = true;
	m_poly->SetUVRect(Walk_U[1]);
}

void Player::OnHitLadder()
{
	if (m_keyFlg)
	{
		if (GetAsyncKeyState('W') & 0x8000) { m_gravity = -0.03f; }
		if (GetAsyncKeyState('S') & 0x8000) { m_gravity = -0.03f; }
		if (GetAsyncKeyState('A') & 0x8000) { m_gravity = -0.03f; }
		if (GetAsyncKeyState('D') & 0x8000) { m_gravity = -0.03f; }
	}
}