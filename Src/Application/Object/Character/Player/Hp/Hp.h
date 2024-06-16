#pragma once
#include"../../CharacterBase.h"
class Hp :public CharacterBase
{
public:
	Hp() {};
	~Hp()override {};

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawSprite()override;

private:
	int m_hp;
};
