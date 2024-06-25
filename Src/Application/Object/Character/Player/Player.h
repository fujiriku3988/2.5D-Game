#pragma once
#include"../../Character/CharacterBase.h"
class Camera;
class Player :public CharacterBase
{
public:
	enum DirType
	{
		Up = 1 << 0,	//上
		Down = 1 << 1,	//下
		Left = 1 << 2,	//左
		Right = 1 << 3	//右
	};

	Player() {}
	~Player() override{}

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;

	void OnHit();
	void OnHitLadder();
	void OnHitGoal();
	//セッター
	void SetCamera(std::shared_ptr<Camera>_camera) { m_wpCamera = _camera; }
	void ResetRot() { m_rot = {}; }
	//ゲッター
	bool GetAliveFlg() { return m_aliveFlg; }
	bool GetGoalFlg() { return m_goalFlg; }
private:
	std::weak_ptr<Camera> m_wpCamera;
	//プレイヤーHP
	int m_nowHp;//現在のHP
	int m_maxHp;//最大のHP
	Math::Vector3 result;
	//アニメーション
	UINT m_dirType;
	int Walk_R[4] = { 6,7,8,7 };//右
	int Walk_L[4] = {3,4,5,4};//左
	int Walk_U[4] = {9,10,11,10};//上
	int Walk_D[4] = {0,1,2,1};//下
	int m_walkWait;
	//当たり判定で使う変数
	int m_time;
	int m_timeFrame;
	//プレイヤーベクトル
	Math::Vector3 m_playerFowardVec;//前ベクター
	Math::Vector3 m_playerSideVec;//横ベクター
	Math::Vector3 m_vecDir;//合成ベクター
	bool m_keyFlg = false;//キー押してるか
	bool m_walkFlg = false;//歩いてるか
	bool m_aliveFlg = true;//生存フラグ
	bool m_goalFlg = false;
};
