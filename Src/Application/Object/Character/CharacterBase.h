#pragma once
class CharacterBase :public KdGameObject
{
public:
	//アニメーション情報
	struct AnimetionInfo
	{
		float count;//現在のコマ数カウント
		float speed;//アニメーションの速度
	};

	CharacterBase() {}
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
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

protected:
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::shared_ptr<KdModelData>m_model = nullptr;
	std::weak_ptr<CharacterBase>m_wpPoly;
	std::weak_ptr<CharacterBase>m_wpModel;
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Rectangle m_rect;
	Math::Vector3 m_pos;
	Math::Vector2 m_spritePos;
	Math::Vector3 m_dir;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_speed;
	float m_gravity;
	bool m_hitFlg = false;
	//行列
	Math::Matrix scaleMat;
	Math::Matrix transMat;
	Math::Matrix rotMatX;
	Math::Matrix rotMatY;
	Math::Matrix rotMatZ;
	//アニメーション
	AnimetionInfo m_anime;
	int m_animeCnt;
	int m_animeCntMAX;
	//音量
	struct volume
	{
		float walk;
		float damage;
	};
	volume m_vol;
};
