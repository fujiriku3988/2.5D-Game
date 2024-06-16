#pragma once
#include"../../Character/CharacterBase.h"
class Player :public CharacterBase
{
public:

	Player() {}
	~Player() override{}

	void Init()override;
	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	void SetCameraPos(Math::Vector3 _camPos) { m_camPos = _camPos; }//カメラのpos座標（使うかも）
	void ResetRot() { m_rot = {}; }
	void OnHit();

private:
	//プレイヤーHP
	int m_hp;
	//アニメーション
	int Walk_R[4] = { 6,7,8,7 };//右
	int Walk_L[4] = {3,4,5,4};//左
	int Walk_U[4] = {9,10,11,10};//上
	int Walk_D[4] = {0,1,2,1};//下
	bool Walk_Rflg = false;
	bool Walk_Lflg = false;
	bool Walk_Uflg = false;
	bool Walk_Dflg = false;
	//当たり判定で使う変数
	bool m_hitFlg;
	int m_time;
	//カメラの座標
	Math::Vector3 m_camPos;
	//プレイヤーベクトル
	Math::Vector3 m_playerFowardVec;//前ベクター
	Math::Vector3 m_playerSideVec;//横ベクター
};
