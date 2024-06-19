#pragma once
class Goal :public KdGameObject
{
public:

	Goal() {};
	~Goal()override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

private:
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
};