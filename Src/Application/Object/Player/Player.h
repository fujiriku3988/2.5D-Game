#pragma once
class Player :public KdGameObject
{
public:

	Player() {};
	~Player() {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void DrawLit()override;
	void DrawUnLit()override;
	void DrawBright()override;


private:
	KdModelData m_model;
	//std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	KdSquarePolygon m_poly;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	//アニメーション
	float m_anima;
	int Walk_R[4] = { 6,7,8,7 };//右
	int Walk_L[4] = {3,4,5,4};//左
	int Walk_U[4] = {9,10,11,10};//上
	int Walk_D[4] = {0,1,2,1};//下
	bool Walk_Rflg = false;
	bool Walk_Lflg = false;
	bool Walk_Uflg = false;
	bool Walk_Dflg = false;
	std::vector<int>m_animaList;
};
