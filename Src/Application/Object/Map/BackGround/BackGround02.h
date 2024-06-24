#pragma once
class BackGround02 :public KdGameObject
{
public:

	BackGround02() {};
	~BackGround02() override {};

	void Init()override;
	void Update()override;
	void DrawSprite()override;


private:
	KdTexture m_tex01;
	KdTexture m_tex02;
	Math::Vector3 m_pos;
	Math::Vector3 m_rot;
	Math::Vector3 m_scale;
	Math::Color m_color;
	Math::Rectangle m_rect;
};