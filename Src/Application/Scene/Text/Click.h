#pragma once
class Click :public KdGameObject
{
public:
	Click() {}
	~Click() {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void ClickOn() { m_clickFlg = true; }

private:
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Vector2 m_spritePos;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_alpha;
	float speed;
	bool m_clickFlg;
};