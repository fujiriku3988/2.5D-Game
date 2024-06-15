#pragma once
class BackGround :public KdGameObject
{
public:

	BackGround() {};
	~BackGround() override{};

	void Init()override;
	void DrawLit()override;


private:
	KdModelData m_model;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
};