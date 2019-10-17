#pragma once
#include "DxLib.h"
#include <random>
#include <cmath>
#include <string>
#include "InputKey.hpp"


class Character
{
public:
	enum class EHitGarbageID { doro, mizutamari, sekiyu };


private:
	const int m_playerDrawNum = 20;
	int mD_playerArray[20];
	int mD_playerArraySpeed[20];

	const int m_playerDrawAnimSpeed = 6;
	int m_playerDrawAnimCount;

	const int m_playerSize = 192;			// プレイヤーの画像サイズ

	const int m_mostMaxY = 1080 - 128;		// プレイヤーの最大最底辺位置
	const int m_defaultX = 284;				// プレイヤーの基準X座標

	int m_playerX;		// プレイヤーのX座標
	int m_playerY;		// プレイヤーのY座標

	int m_prePlayerX;
	int m_prePlayerY;

	enum class ESTATE { normal, speedUp, speedMAX, speedDown, damageHit, heal, doroDamageHit };
	ESTATE m_nowState;				// 現在の状態

	int m_frameCount;


	void PositionProcess();


	/// 縮小----------------------------------------------------

	float m_smallSpeed;

	/// --------------------------------------------------------


	/// ダメージ関連--------------------------------------------

	int m_damageCount;						// ダメージを受けた演出のカウント

	const int m_damageMaxCount = 30;		// ダメージを受けた演出のカウントの最大

	bool m_isDamageHit;						// ダメージを受けたかどうか

	float m_preDamageMAXSpeed;

	const float m_damageDownSpeed = -1.25f;

	void HitGarbageProcess();

	int m_isHitGarbage;

	int m_hitGarbageID;
	int m_preHitGarbageID;

	EHitGarbageID m_hitGarbageObjectID;

	bool m_nowHeal;
	/// --------------------------------------------------------


	/// スピード関連-------------------------------------------

	bool m_isNowSpeedUp;

	const float m_playerMaxSpeed = 70;			// プレイヤーの最大速度

	float m_nowSpeed;							// 現在のスピード

	int m_nowSpeedThirdDigit;		// 現在の速度の三桁目の数字
	int m_nowSpeedSecondDigit;		// 現在の速度の二桁目の数字
	int m_nowSpeedFirstDigit;		// 現在の速度の二桁目の数字
	int m_nowSpeedDecimalPoint;		// 現在の速度の小数点の数字

	float m_addSpeed;							// 加算するスピード値

	float m_speedUpCount;				// 加速が完了するまでの時間

	int m_speedMaxWaitCount;		// 加速最大値の時に持続する時間

	const int m_speedMaxWaitMaxCount = 40;		// 加速最大値の時に持続する時間の最大(2で割り切れないと少しずれる

	const int m_runFirstPlayerAnim = m_playerDrawAnimSpeed * 13;	// 急加速したときの石鹸君のフレームコマ

	int m_speedUpChargeCount;

	const int m_speedUpChargeMax = 420;

	void SpeedProcess();

	void SpeedUpProcess();
	/// --------------------------------------------------------


	/// ジャンプ関連--------------------------------------------

	int m_playerUnderY;		// プレイヤーの足元のY座標

	bool m_isGroundFlag;	// 地面に触れてるか

	bool m_isJumpFlag;	// ジャンプしているか

	bool m_isLongJump;	// 長押しジャンプか

	int m_jumpPower;	// ジャンプ力

	int m_gravityPower;	// 重力

	const int m_jumpMaxPower = 120;		// ジャンプ力の最大値

	const int m_jumpMinPower = 24;		// ジャンプ力の最小値

	const int m_jumpAddPower = 16;		// ジャンプ中の上昇値

	const int m_jumpGravityEnergy = 8;	// ジャンプ中の減少値

	const int m_jumpFirstPlayerAnim = m_playerDrawAnimSpeed * 8;	// ジャンプしたときの石鹸君のフレームコマ

	bool m_isFlyDamageHit;

	void PlayerJump();
	/// --------------------------------------------------------

	/// 速度表示

	int mD_speedNumber[10];
	int mD_speedComma;
	/// --------------------------------------------------------


	int m_allNowAreaX;


public:
	Character();
	~Character();


	// 描画
	void Draw();

	void BlurDraw();

	// プロセス
	void Process();


	const bool& GetIsSpeedUp() const;

	const float& GetSpeed() const;

	const float& GetDefaultMAXSpeed() const;

	void HitGarbageNow(int t_garbageID, EHitGarbageID t_garbageObjectID);

	const int& GetAreaX() const;

	const int& GetAreaY() const;

	const int GetSize() const;

	int GetAllNowAreaX() { return m_allNowAreaX; }

	void SetReset() { m_smallSpeed = 0.0f; }

	const bool GetNowDamage() const;

	const bool GetNowHeal() const;
};

