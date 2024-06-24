#pragma once
#include"../../Character/CharacterBase.h"
class Camera;
class TitlePlayer :public CharacterBase
{
public:
	enum DirType
	{
		Up = 1 << 0,	//上
		Down = 1 << 1,	//下
		Left = 1 << 2,	//左
		Right = 1 << 3	//右
	};

	TitlePlayer() {}
	~TitlePlayer() override {}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;

	void AnimeOn() { m_animeFlg = true; }
private:
	//アニメーション
	UINT m_dirType;
	int Walk_U[4] = { 0,1,2,1 };//上
	bool m_keyFlg = false;//キー押してるか
	bool m_animeFlg = false;
	Math::Vector2 m_texSize;
};
