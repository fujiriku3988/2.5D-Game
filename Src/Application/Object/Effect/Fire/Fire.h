#pragma once
#include "../BaseEffect.h"
#include"Effects.h"
class Fire :public BaseEffect
{
public:
	Fire() {};
	~Fire()override {}

	void Init()override;
	void DrawBright()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void OnHit()override;

	void SetEffectPoly(std::shared_ptr<BaseEffect>_poly) { m_wpPoly = _poly; }
	void SetFirePos(Math::Vector3 _pos) { m_pos = _pos; }
private:
	float m_dissolve;
	float m_dissolveMAX;
	float m_dissolveSpeed;
};