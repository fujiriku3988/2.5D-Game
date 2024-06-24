#pragma once

#include "../Scene/SceneManager.h"

class Fade
{
public:

	void Update();
	void Draw();

	void UpdateBlackFade();
	void UpdateWhiteFade();

	void BootBlackFade(SceneManager::SceneType _type);
	void BootWhiteFade(SceneManager::SceneType _type);

	bool GetFade() { return m_bFade; }
private:

	void Init();

	SceneManager::SceneType m_nextScene;

	bool m_bFade;			// フェード中かどうか？
	bool m_bFadeOut;		// フェードアウト？
	bool m_bFadeIn;			// フェードイン？
	bool m_bColor;			// 黒か白か？(true 白:false 黒)

	// 黒(1280*720)
	KdTexture m_blackTex;
	Math::Matrix m_blackMat;
	Math::Color m_blackColor;
	float m_blackAlpha;
	
	// 白(1280*720)
	KdTexture m_whiteTex;
	Math::Matrix m_whiteMat;
	Math::Color m_whiteColor;
	float m_whiteAlpha;

private:

	Fade() { Init(); }
	~Fade() {}

public:

	static Fade& Instance()
	{
		static Fade instance;
		return instance;
	}
};