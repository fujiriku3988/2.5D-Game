#pragma once
#include"../../Character/CharacterBase.h"
class Fire;
class Enemy01 :public CharacterBase
{
public:

	Enemy01() {};
	~Enemy01()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

private:
	std::shared_ptr<Fire>fire = nullptr;
	int m_coolTime;
	bool m_fire;
};
