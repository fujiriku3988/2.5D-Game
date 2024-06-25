#pragma once
class GameOver :public KdGameObject
{
public:
	GameOver() {}
	~GameOver() {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Vector2 m_spritePos;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_alpha;
	float m_alphaMAX;
	float m_alphaSpeed;
	float m_time;
};