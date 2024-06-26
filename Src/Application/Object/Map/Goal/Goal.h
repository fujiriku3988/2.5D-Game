﻿#pragma once
class Goal :public KdGameObject
{
public:

	Goal() {};
	~Goal()override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:
	std::shared_ptr<KdSquarePolygon>m_poly = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_alpha;
	float m_alphaMAX;
	float m_alphaMIN;
	float m_alSpeed;
};