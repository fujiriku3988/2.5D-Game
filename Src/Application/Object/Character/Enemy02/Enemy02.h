#pragma once
#include"../../Character/CharacterBase.h"
class Enemy02 :public CharacterBase
{
public:

	Enemy02() {};
	~Enemy02()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

private:
	float m_angle;
	int m_fly[5] = { 0,1,2,3,4 };
};
