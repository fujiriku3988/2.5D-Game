﻿#pragma once
class Tree :public KdGameObject
{
public:

	Tree() {};
	~Tree()override {};

	void Init()override;
	void Update()override;
	void DrawLit()override;


private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
};