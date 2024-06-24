#pragma once
#include"../BaseScene/BaseScene.h"
class TitlePlayer;
class Click;
class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init() override;
	std::weak_ptr<TitlePlayer>m_player;
	std::weak_ptr<Click>m_click;
	bool m_keyFlg = false;
};
