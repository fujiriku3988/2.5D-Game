#pragma once
#include "../BaseEffect.h"
#include"Effects.h"
class Fire :public BaseEffect
{
public:
	Fire() {};
	~Fire()override {}

	void Init()override;
	void DrawLit()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void OnHit()override;

	void SetEffectPoly(std::shared_ptr<BaseEffect>_poly) { m_wpPoly = _poly; }
	void SetFirePos(Math::Vector3 _pos) { m_pos = _pos; }
private:
	float dissolve;
};