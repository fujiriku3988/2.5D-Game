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
	bool GetClickFlg() { return m_clickFlg; }

private:
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Vector2 m_spritePos;
	Math::Vector3 m_scale;
	Math::Color m_color;
	float m_alpha;
	float m_alphaMAX;
	float m_alphaMIN;
	float speed;
	bool m_clickFlg;
};