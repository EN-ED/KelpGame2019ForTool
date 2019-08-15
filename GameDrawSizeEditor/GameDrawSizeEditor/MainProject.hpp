#pragma once
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>


class MainProject
{
private:
	// csv�f�[�^�̓ǂݍ���
	void TextRead();

	// csv�f�[�^��ۑ�����
	std::vector<std::vector<std::string>> vv_csvData;

	// ���W���Z�[�u����
	void TextOutPut();
	
	// �}�E�X�̈ʒu
	int m_mouseX, m_mouseY;

	// ���O�̃}�E�X�̈ʒu
	int m_preMouseX, m_preMouseY;

	// �}�E�X���N���b�N���Ă��邩�ǂ���
	int m_isMouseClick;

	// �X�N���[�����W
	int m_scrollX;

	// �X�N���[���X�s�[�h
	int m_scrollSpeed;

	// �X�N���[�������邩�ǂ���
	int m_isScroll;


	/// --------------------------------------------------
	// �w�i�摜
	int m_backGroundDraw;


	/// --------------------------------------------------
	// �L�����N�^�[�R�}�̖���
	int m_charaXNum, m_charaYNum;

	// �L�����N�^�[�R�}�̃T�C�Y
	int m_charaXSize, m_charaYSize;

	// �L�����N�^�[�R�}�̑�����
	int m_charaNum;

	// �L�����N�^�[�摜
	int m_charaDraw[64];

	// �L�����N�^�[�̍��W
	int m_charaAreaX;

	// �L�����N�^�[�𓮂����Ă���Œ����ǂ���
	int m_isClickChara;


	/// --------------------------------------------------
	// �ǂ���������̂̉摜
	int m_chaserDraw[64];

	// �ǂ���������̂̉摜�T�C�Y
	int m_chaserXSize, m_chaserYSize;

	// �ǂ���������̂̃R�}�̖���
	int m_chaserXNum, m_chaserYNum;

	// �ǂ���������̂̃R�}�̑�����
	int m_chaserNum;


	/// --------------------------------------------------
	// ��Q���̉摜
	int m_garbageDraw;

	// ��Q���̉摜�T�C�Y
	int m_garbageXSize, m_garbageYSize;


	/// --------------------------------------------------
	// �n�ʂ̉摜
	int m_underGroundDraw;

	// �n�ʂ̉摜�T�C�Y
	int m_underGroundXSize, m_underGroundYSize;


	/// --------------------------------------------------
	// ���x�o�߂̉摜
	int m_fasterDraw;

	// ���x�o�߂̉摜�T�C�Y
	int m_fasterXSize, m_fasterYSize;

	// ���x�o�߂̍��W
	int m_fasterAreaX, m_fasterAreaY;

	// ���x�o�߂𓮂����Ă���Œ����ǂ���
	int m_isClickFaster;


public:
	MainProject();
	~MainProject();


	void Draw();
	void Process();
};

