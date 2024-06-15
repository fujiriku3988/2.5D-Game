#pragma once
#include "../BaseEffect.h"
#include"Effects.h"
class Fire :public BaseEffect
{
public:
	Fire() {};
	~Fire()override {}

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	void SetFirePos(Math::Vector3 _pos) { m_pos = _pos; }
private:

};