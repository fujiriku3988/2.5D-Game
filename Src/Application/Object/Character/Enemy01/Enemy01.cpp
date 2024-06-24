#include "Enemy01.h"
#include"../../../Scene/SceneManager.h"
#include"../../Effect/Fire/Fire.h"

void Enemy01::Init()
{
	CharacterBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy01/enemy01.png");
	m_pos = {};
	m_scale = { 1 };
	m_color = { 1,1,1,1 };
	m_speed = 0.1f;
	m_poly->SetSplit(3, 4);
	m_poly->SetUVRect(0);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_fire = false;
	m_coolTime = 30;
	m_objType = KdGameObject::eEnemy;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("dragon", { 0,0.5f,0 }, 0.3f, KdCollider::TypeDamage);
}

void Enemy01::PreUpdate()
{
	m_coolTime--;
	if (m_coolTime <= 0)
	{
		m_coolTime = 0;
		m_fire = true;
	}
	if (m_fire)
	{
		fire = std::make_shared<Fire>();
		fire->Init();
		fire->SetFirePos(m_pos+Math::Vector3{0.0f,0.0f,0.0f});
		SceneManager::Instance().AddObject(fire);
		m_coolTime = 30;
		m_fire = false;
	}
}

void Enemy01::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0 }, 0.3f, kGreenColor);

	m_gravity += 0.005f;
	m_pos.y -= m_gravity;
}

void Enemy01::PostUpdate()
{
	//レイ情報
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
		m_pos = hitPos;
		m_gravity = 0;
	}

	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatY = Math::Matrix::CreateRotationY(30);
	m_mWorld = scaleMat * rotMatY * transMat;
}
