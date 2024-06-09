#pragma once
#include"../../Character/CharacterBase.h"
class Enemy01 :public CharacterBase
{
public:

	Enemy01() {};
	~Enemy01() {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

private:
};
