#include "MainProject.hpp"
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include "DxLib.h"
#include <random>



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::TextOutPut()
{
	std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
	std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
	std::uniform_int_distribution<> rand(10000, 99999);        // [0, 99] �͈͂̈�l����
	std::string randStr = "media\\Save\\" + std::to_string(rand(mt)) + ".csv";
	// �t�@�C����ǂݍ���
	std::ofstream saveFile(randStr.c_str());


	// �t�@�C���ǂݍ��ݎ��s
	if (saveFile.fail())
	{
		return;
	}


	saveFile << "soap" << "," << m_charaAreaX << std::endl << "chaser" << "," << m_chaserAreaX << std::endl;


	// �t�@�C�������
	saveFile.close();


	m_saveCount = 255;
}



/// ---------------------------------------------------------------------------------------------------------------------
MainProject::MainProject()
{
	std::string mediaStr = "media\\";
	std::string addStr = "";


	// �w�i
	m_backGroundDraw	 = LoadGraph("media\\background.png");

	m_scrollX = 0;
	m_scrollSpeed = 2;


	// �L�����N�^�[	
	for (int i = 0; i != m_charaNum; ++i)
	{
		std::string str = "media\\anim_blink\\" + std::to_string(i) + ".png";
		m_charaDraw[i] = LoadGraph(str.c_str());
	}
	m_charaAreaX = 284;
	m_playerDrawAnimCount = 0;


	// �ǂ����������
	for (int i = 0; i != m_chaserNum; ++i)
	{
		std::string str = "media\\tkms_anim01\\" + std::to_string(i) + ".png";
		m_chaserDraw[i] = LoadGraph(str.c_str());
	}
	m_chaserAreaX = 0;
	m_chaserSpeedCount = 0;


	// �n��
	m_underGroundDraw	 = LoadGraph("media\\underground.png");


	// �}�E�X
	m_isMouseClick = false;
	m_isClickChara = false;
	m_isClickChaser = false;


	m_saveCount = 0;
}



/// ---------------------------------------------------------------------------------------------------------------------
MainProject::~MainProject()
{
	DeleteGraph(m_backGroundDraw);
	for (int i = 0; i != m_charaNum; ++i)
	{
		DeleteGraph(m_charaDraw[i]);
	}
	for (int i = 0; i != m_chaserNum; ++i)
	{
		DeleteGraph(m_chaserDraw[i]);
	}
	DeleteGraph(m_underGroundDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::Draw()
{
	// �w�i
	DrawGraph(m_scrollX, 0, m_backGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 0, m_backGroundDraw, true);

	// �n��
	DrawGraph(m_scrollX, 1080 - 128, m_underGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 1080 - 128, m_underGroundDraw, true);

	// �ǂ����������
	DrawGraph(m_chaserAreaX, 1080 - 128 - 512, m_chaserDraw[static_cast<int>(m_chaserSpeedCount / m_chasrArraySpeed)], true);
	DrawBox(m_chaserAreaX, 1080 - 128 - 512, m_chaserAreaX + 512, 1080 - 128, GetColor(0, 0, 0), false);
	DrawFormatString(m_chaserAreaX + 492, 1080 - 128 - 512 - 20, GetColor(0, 0, 0), "%d x %d", m_chaserAreaX, 1080 - 128 - 512);

	// �L�����N�^�[
	DrawGraph(m_charaAreaX, 1080 - 128 - 192, m_charaDraw[static_cast<int>(m_playerDrawAnimCount / m_playerDrawAnimSpeed)], true);
	DrawBox(m_charaAreaX, 1080 - 128 - 192, m_charaAreaX + 192, 1080 - 128, GetColor(0, 0, 0), false);
	DrawFormatString(m_charaAreaX, 1080 - 128 - 192 - 20, GetColor(0, 0, 0), "%d x %d", m_charaAreaX, 1080 - 128 - 192);

	// �}�E�X
	DrawFormatString(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, GetColor(0, 0, 0), "%d x %d", MouseData::GetMouseArea().x, MouseData::GetMouseArea().y);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_saveCount);
	DrawFormatString(255, 255, GetColor(0, 255, 255), "�Z�[�u���܂�����������������������������������������");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	DrawFormatString(0, 0, GetColor(0, 0, 0), "�ۑ��FS�L�[\n�ʒu���Z�b�g�FR�L�[\n�����F���}�E�X");
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::Process()
{
	if (++m_playerDrawAnimCount >= m_playerDrawAnimSpeed * m_charaNum) m_playerDrawAnimCount = 0;
	if (++m_chaserSpeedCount >= m_chasrArraySpeed * m_chaserNum) m_chaserSpeedCount = 0;
	if (m_saveCount > 0) m_saveCount--;


	// �}�E�X�̈ʒu���擾����
	if (MouseData::GetClick(MouseData::ECLICK::LEFT) >= 1)
	{
		m_isMouseClick = true;
	}
	else
	{
		m_isMouseClick = false;
		m_isClickChara = false;
		m_isClickChaser = false;
	}



	// �ʒu������������
	if (KeyData::Get(KEY_INPUT_R) == 1)
	{
		m_charaAreaX = 980;
		m_chaserAreaX = 0;
		m_scrollX = 0;
	}


	// �Z�[�u����
	if (KeyData::Get(KEY_INPUT_S) == 1)
	{
		TextOutPut();
	}


	// ���W�𓮂���
	if (m_isMouseClick)
	{
		if (MouseData::GetMouseArea().x > m_charaAreaX
			&& MouseData::GetMouseArea().x < m_charaAreaX + 192
			&& MouseData::GetMouseArea().y >  1080 - 128 - 192
			&& MouseData::GetMouseArea().y < 1080 - 128)
		{
			m_isClickChara = true;
		}
		if (m_isClickChara)
		{
			m_charaAreaX += MouseData::GetMouseMoveValue().x;
		}


		if (MouseData::GetMouseArea().x > m_chaserAreaX
			&& MouseData::GetMouseArea().x < m_chaserAreaX + 512
			&& MouseData::GetMouseArea().y >  1080 - 128 - 512
			&& MouseData::GetMouseArea().y < 1080 - 128)
		{
			m_isClickChaser = true;
		}
		if (m_isClickChaser)
		{
			m_chaserAreaX += MouseData::GetMouseMoveValue().x;
		}
	}


	// �X�N���[��������
	m_scrollX -= m_scrollSpeed;
	if (m_scrollX <= -1920)
	{
		m_scrollX = 0;
	}
}
