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
	Math::Vector2 m_texSize;
	Math::Vector3 m_spritePos;
	Math::Color m_color;
	Math::Rectangle m_rect;
};