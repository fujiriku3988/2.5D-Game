#pragma once
class BaseEffect :public KdGameObject
{
public:
	BaseEffect() {};
	~BaseEffect()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void SetEffectPoly(std::shared_ptr<BaseEffect>_poly) { m_wpPoly = _poly; }
	//void SetEffectPos(Math::Vector3 _pos) { m_pos = _pos; }
protected:
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelData>m_model = nullptr;
	std::weak_ptr<BaseEffect>m_wpPoly;
	std::weak_ptr<BaseEffect>m_wpModel;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	Math::Vector3 m_dir;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	float m_speed;
	Math::Matrix scaleMat;
	Math::Matrix transMat;
	Math::Matrix rotMatX;
	Math::Matrix rotMatY;
	Math::Matrix rotMatZ;
	//アニメーション
	float m_anime;
	float m_animeSpeed;
};
