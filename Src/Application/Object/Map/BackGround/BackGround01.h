#pragma once
class BackGround01 :public KdGameObject
{
public:

	BackGround01() {};
	~BackGround01() override{};

	void Init()override;
	void Update()override;
	void DrawLit()override;


private:
	KdModelData m_model;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
};