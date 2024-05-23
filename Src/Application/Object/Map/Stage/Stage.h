#pragma once
class Stage :public KdGameObject
{
public:

	Stage() {};
	~Stage() {};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawUnLit()override;
	void DrawBright()override;


private:
	KdModelData m_model;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
};