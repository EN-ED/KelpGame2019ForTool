#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


class MainProject
{
private:
	// ���W���Z�[�u����
	void TextOutPut();

	// �}�E�X���N���b�N���Ă��邩�ǂ���
	int m_isMouseClick;

	// �X�N���[�����W
	int m_scrollX;

	// �X�N���[���X�s�[�h
	int m_scrollSpeed;


	/// --------------------------------------------------
	// �w�i�摜
	int m_backGroundDraw;


	/// --------------------------------------------------
	// �L�����N�^�[�R�}�̑�����
	const int m_charaNum = 20;

	// �L�����N�^�[�摜
	int m_charaDraw[20];

	// �L�����N�^�[�̍��W
	int m_charaAreaX;

	// �L�����N�^�[�𓮂����Ă���Œ����ǂ���
	int m_isClickChara;

	// �摜���[�V�������x
	const int m_playerDrawAnimSpeed = 6;
	int m_playerDrawAnimCount;


	/// --------------------------------------------------
	// �ǂ���������̂̉摜
	int m_chaserDraw[31];

	// �ǂ���������̂̃R�}�̑�����
	const int m_chaserNum = 31;

	// �ǂ���������̂̍��W
	int m_chaserAreaX;

	// �ǂ���������̂𓮂����Ă���Œ����ǂ���
	int m_isClickChaser;

	// �摜���[�V�������x
	int m_chaserSpeedCount;
	const int m_chasrArraySpeed = 2;


	/// --------------------------------------------------
	// �n�ʂ̉摜
	int m_underGroundDraw;


	int m_saveCount;


public:
	MainProject();
	~MainProject();


	void Draw();
	void Process();
};

