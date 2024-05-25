#pragma once
#include"../BaseScene/BaseScene.h"
class Player;
class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	Math::Vector3 m_camPos;
	Math::Vector3 m_camRot;
	float m_camRad;
	std::weak_ptr<Player>m_player;
};
