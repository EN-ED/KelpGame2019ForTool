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

	const int m_playerSize = 192;			// �v���C���[�̉摜�T�C�Y

	const int m_mostMaxY = 1080 - 128;		// �v���C���[�̍ő�Œ�ӈʒu
	const int m_defaultX = 284;				// �v���C���[�̊X���W

	int m_playerX;		// �v���C���[��X���W
	int m_playerY;		// �v���C���[��Y���W

	int m_prePlayerX;
	int m_prePlayerY;

	enum class ESTATE { normal, speedUp, speedMAX, speedDown, damageHit, heal, doroDamageHit };
	ESTATE m_nowState;				// ���݂̏��

	int m_frameCount;


	void PositionProcess();


	/// �k��----------------------------------------------------

	float m_smallSpeed;

	/// --------------------------------------------------------


	/// �_���[�W�֘A--------------------------------------------

	int m_damageCount;						// �_���[�W���󂯂����o�̃J�E���g

	const int m_damageMaxCount = 30;		// �_���[�W���󂯂����o�̃J�E���g�̍ő�

	bool m_isDamageHit;						// �_���[�W���󂯂����ǂ���

	float m_preDamageMAXSpeed;

	const float m_damageDownSpeed = -1.25f;

	void HitGarbageProcess();

	int m_isHitGarbage;

	int m_hitGarbageID;
	int m_preHitGarbageID;

	EHitGarbageID m_hitGarbageObjectID;

	bool m_nowHeal;
	/// --------------------------------------------------------


	/// �X�s�[�h�֘A-------------------------------------------

	bool m_isNowSpeedUp;

	const float m_playerMaxSpeed = 70;			// �v���C���[�̍ő呬�x

	float m_nowSpeed;							// ���݂̃X�s�[�h

	int m_nowSpeedThirdDigit;		// ���݂̑��x�̎O���ڂ̐���
	int m_nowSpeedSecondDigit;		// ���݂̑��x�̓񌅖ڂ̐���
	int m_nowSpeedFirstDigit;		// ���݂̑��x�̓񌅖ڂ̐���
	int m_nowSpeedDecimalPoint;		// ���݂̑��x�̏����_�̐���

	float m_addSpeed;							// ���Z����X�s�[�h�l

	float m_speedUpCount;				// ��������������܂ł̎���

	int m_speedMaxWaitCount;		// �����ő�l�̎��Ɏ������鎞��

	const int m_speedMaxWaitMaxCount = 40;		// �����ő�l�̎��Ɏ������鎞�Ԃ̍ő�(2�Ŋ���؂�Ȃ��Ə��������

	const int m_runFirstPlayerAnim = m_playerDrawAnimSpeed * 13;	// �}���������Ƃ��̐Ό��N�̃t���[���R�}

	int m_speedUpChargeCount;

	const int m_speedUpChargeMax = 420;

	void SpeedProcess();

	void SpeedUpProcess();
	/// --------------------------------------------------------


	/// �W�����v�֘A--------------------------------------------

	int m_playerUnderY;		// �v���C���[�̑�����Y���W

	bool m_isGroundFlag;	// �n�ʂɐG��Ă邩

	bool m_isJumpFlag;	// �W�����v���Ă��邩

	bool m_isLongJump;	// �������W�����v��

	int m_jumpPower;	// �W�����v��

	int m_gravityPower;	// �d��

	const int m_jumpMaxPower = 120;		// �W�����v�͂̍ő�l

	const int m_jumpMinPower = 24;		// �W�����v�͂̍ŏ��l

	const int m_jumpAddPower = 16;		// �W�����v���̏㏸�l

	const int m_jumpGravityEnergy = 8;	// �W�����v���̌����l

	const int m_jumpFirstPlayerAnim = m_playerDrawAnimSpeed * 8;	// �W�����v�����Ƃ��̐Ό��N�̃t���[���R�}

	bool m_isFlyDamageHit;

	void PlayerJump();
	/// --------------------------------------------------------

	/// ���x�\��

	int mD_speedNumber[10];
	int mD_speedComma;
	/// --------------------------------------------------------


	int m_allNowAreaX;


public:
	Character();
	~Character();


	// �`��
	void Draw();

	void BlurDraw();

	// �v���Z�X
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

