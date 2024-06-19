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
	int m_coolTime = 0;
	bool m_fire = false;
};
