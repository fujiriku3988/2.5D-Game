#include "Enemy02.h"
#include"../../../Scene/SceneManager.h"

void Enemy02::Init()
{
	CharacterBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy02/enemy02.png");//横１列の画像,rectでアニメーション
	m_pos = {};
	m_scale = { 1 };
	m_color = { 1,1,1,1 };
	m_speed = 0.1f;
	m_angle = 0;
	m_poly->SetSplit(5, 1);
	m_poly->SetUVRect(0);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_objType = KdGameObject::eEnemy;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("bee", { 0,0.5f,0 }, 0.4f, KdCollider::TypeDamage);
}

void Enemy02::PreUpdate()
{
}

void Enemy02::Update()
{
	//m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3{ 0,0.5f,0 }, 0.3f, kGreenColor);

	//サインカーブをやる
	m_angle += 1.0f;
	if (m_angle >= 360.0f)
	{
		m_angle += -360.0f;
	}
	m_pos.y += sin(DirectX::XMConvertToRadians(m_angle))*0.02;
}

void Enemy02::PostUpdate()
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

	scaleMat = Math::Matrix::CreateScale(m_scale);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	rotMatY = Math::Matrix::CreateRotationY(30);
	m_mWorld = scaleMat * rotMatY * transMat;
}
