#pragma once
class Player;

class BaseGate :public KdGameObject
{
public:
	BaseGate() {};
	~BaseGate()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawBright()override;

	void SetPlayer(std::shared_ptr<Player>_player) { m_player = _player; }
	void OnHit();
protected:
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	std::weak_ptr<Player>m_player;
	//std::shared_ptr<Player>m_player;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	Math::Vector3 m_dir;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	Math::Matrix scaleMat;
	Math::Matrix transMat;
	Math::Matrix rotMatX;
	Math::Matrix rotMatY;
	Math::Matrix rotMatZ;
	int m_warp[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	//アニメーション
	float m_anime;
	float m_animeSpeed;
	//音量
	float m_vol;
};
