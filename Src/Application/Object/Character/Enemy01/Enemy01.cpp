#include "Enemy01.h"
#include"../../../Scene/SceneManager.h"
#include"../../Effect/Fire/Fire.h"

void Enemy01::Init()
{
	CharacterBase::Init();
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/obj/enemy01/enemy01.png");
	m_pos = { 1.8f,10,0 };
	m_scale = { 1 };
	m_speed = 0.1f;
	m_poly->SetSplit(3, 4);
	m_poly->SetUVRect(0);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	/*fire = std::make_shared<Fire>();
	fire->Init();
	SceneManager::Instance().AddObject(fire);*/
}

void Enemy01::PreUpdate()
{
}

void Enemy01::Update()
{
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
}

void Enemy01::PostUpdate()
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
	rotMatY = Math::Matrix::CreateRotationY(30);
	m_mWorld = scaleMat * rotMatY * transMat;
}
