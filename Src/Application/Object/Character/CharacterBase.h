#pragma once
class CharacterBase :public KdGameObject
{
public:
	CharacterBase() {};
	~CharacterBase()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;
	void GenerateDepthMapFromLight()override;

	void SetCharacterPoly(std::shared_ptr<CharacterBase>_poly) { m_wpPoly = _poly; }
	void SetCharacterModel(std::shared_ptr<CharacterBase>_model) { m_wpModel = _model; }
	
protected:
	//KdModelData m_model;
	//KdSquarePolygon m_poly;
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelData>m_model = nullptr;
	std::weak_ptr<CharacterBase>m_wpPoly;
	std::weak_ptr<CharacterBase>m_wpModel;
	KdTexture m_tex;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	Math::Vector3 m_dir;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_speed;
	Math::Matrix scaleMat;
	Math::Matrix transMat;
	Math::Matrix rotMatX;
	Math::Matrix rotMatY;
	Math::Matrix rotMatZ;
	//アニメーション
	float m_anime;
	float m_animeSpeed;
	float m_gravity;
};
