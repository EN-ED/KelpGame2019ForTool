#include "Project.hpp"
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include "DxLib.h"

#include <random>
#include <fstream>
#include <sstream>



/// ---------------------------------------------------------------------------------------------------------------------
void Project::TextOutPut()
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


	saveFile << "�Ȃ�" << std::endl;
	for (int i = 0; i != m_vChipAreaX.size(); ++i)
	{
		saveFile << m_vChipAreaX.at(i) << "," << m_vChipAreaY.at(i) << std::endl;
	}


	// �t�@�C�������
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::GameDraw()
{
	// �w�i
	DrawGraph(m_scrollX, 0, m_backGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 0, m_backGroundDraw, true);

	// �n��
	DrawGraph(m_scrollX, 1080 - 128 /*�S�̍��� - �n�ʍ���*/, m_underGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 1080 - 128 /*�S�̍��� - �n�ʍ���*/, m_underGroundDraw, true);

	// �}�b�v�`�b�v
	for (int i = 0; i != m_vChipAreaX.size(); ++i)
	{
		DrawGraph(m_vChipAreaX.at(i) - m_areaX + 1920, m_vChipAreaY.at(i), m_vChipDraw, true);
	}

	// �L�����N�^�[
	DrawGraph(284, 1080 - 128 - 192 /*�S�̍��� - �n�ʍ��� - �L�����N�^�[����*/, m_charaDraw, true);
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::GridDraw()
{
	if (m_is96DotGrid)
	{
		for (int i = m_scrollX; i <= 1920 - m_scrollX; i += 96)
		{
			DrawLine(i, 0, i, 1080, GetColor(0, 0, 50));
		}
		for (int i = 0; i <= 1080; i += 96)
		{
			DrawLine(0, i, 1920, i, GetColor(0, 0, 50));
		}
	}
	if (m_is64DotGrid)
	{
		for (int i = m_scrollX; i <= 1920 - m_scrollX; i += 64)
		{
			DrawLine(i, 0, i, 1080, GetColor(0, 50, 0));
		}
		for (int i = 0; i <= 1080; i += 64)
		{
			DrawLine(0, i, 1920, i, GetColor(0, 50, 0));
		}
	}
	if (m_is32DotGrid)
	{
		for (int i = m_scrollX; i <= 1920 - m_scrollX; i += 32)
		{
			DrawLine(i, 0, i, 1080, GetColor(50, 0, 0));
		}
		for (int i = 0; i <= 1080; i += 32)
		{
			DrawLine(0, i, 1920, i, GetColor(50, 0, 0));
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::MouseDraw()
{
	// �`�b�v
	DrawGraph(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, m_vChipDraw, true);

	// �}�E�X
	DrawFormatString(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, GetColor(0, 0, 0), "%d x %d", m_mouseAreaX, MouseData::GetMouseArea().y);
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::SpeedManageDraw()
{
	DrawBox(60, 1080 - 54, 1920 - 60, 1080 - 74, GetColor(255, 255, 255), true);

	DrawBox((m_scrollSpeed * 10) - 10 + 60, 1080 - 48, (m_scrollSpeed * 10) + 10 + 60, 1080 - 82, GetColor(125, 0, 0), true);

	DrawBox(19, 1080 - 111, 100, 1080 - 90, GetColor(0, 0, 0), true);

	DrawFormatString(20, 1080 - 110, GetColor(255, 255, 255), "%d", m_scrollSpeed);
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::SideScrollProcess()
{
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		if (++m_scrollSpeed >= 1920) m_scrollSpeed = 1919;
	}
	if (KeyData::Get(KEY_INPUT_X) == 1 && m_scrollSpeed != 0)
	{
		m_scrollSpeed--;
	}
	if (KeyData::Get(KEY_INPUT_R) == 1)
	{
		m_areaX = 1920;
		m_scrollX = 0;
		m_scrollSpeed = 0;
	}
	if (KeyData::Get(KEY_INPUT_RIGHT) >= 1)
	{
		m_areaX += m_scrollSpeed;
		m_scrollX -= m_scrollSpeed;
	}
	if (KeyData::Get(KEY_INPUT_LEFT) >= 1 && m_areaX > 1920)
	{
		m_areaX -= m_scrollSpeed;
		m_scrollX += m_scrollSpeed;
	}
	if (m_scrollX <= -1920)
	{
		m_scrollX = 0;
	}
	if (m_scrollX > 0)
	{
		m_scrollX = -1920;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::GridProcess()
{
	if (KeyData::Get(KEY_INPUT_V) == 1)
	{
		m_is32DotGrid = !m_is32DotGrid;
	}
	if (KeyData::Get(KEY_INPUT_B) == 1)
	{
		m_is64DotGrid = !m_is64DotGrid;
	}
	if (KeyData::Get(KEY_INPUT_N) == 1)
	{
		m_is96DotGrid = !m_is96DotGrid;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::ChipProcess()
{
	// �`�b�v�z�u
	if (MouseData::GetMouseArea().y < 1080 - 128)
	{
		if (MouseData::GetClick(MouseData::ECLICK::LEFT) == 1)
		{
			m_vChipAreaX.push_back(m_mouseAreaX);
			m_vChipAreaY.push_back(MouseData::GetMouseArea().y);
		}
	}


	// �`�b�v�폜
	if (MouseData::GetClick(MouseData::ECLICK::RIGHT) == 1)
	{
		for (int i = 0; i != m_vChipAreaX.size(); ++i)
		{
			int graphX, graphY;
			GetGraphSize(m_vChipDraw, &graphX, &graphY);
			if (m_mouseAreaX > m_vChipAreaX.at(i) && m_mouseAreaX < m_vChipAreaX.at(i) + graphX
				&& MouseData::GetMouseArea().y>m_vChipAreaY.at(i) && MouseData::GetMouseArea().y < m_vChipAreaY.at(i) + graphY)
			{
				m_vChipAreaX.erase(m_vChipAreaX.begin() + i);
				m_vChipAreaY.erase(m_vChipAreaY.begin() + i);
				break;
			}
		}
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
Project::Project()
{
	// �w�i
	m_backGroundDraw = LoadGraph("media\\background.png");
	
	m_scrollX = 0;
	m_scrollSpeed = 0;

	m_is32DotGrid = false;
	m_is64DotGrid = false;
	m_is96DotGrid = false;


	m_vChipDraw = LoadGraph("media\\garbage.png");

	m_areaX = 1920;

	std::vector<int>().swap(m_vChipAreaX);
	std::vector<int>().swap(m_vChipAreaY);

	// �L�����N�^�[
	m_charaDraw = LoadGraph("media\\player.png");


	// �n��
	m_underGroundDraw = LoadGraph("media\\underground.png");


	// �}�E�X
	m_mouseAreaX = MouseData::GetMouseArea().x + m_areaX - 1920;
}



/// ---------------------------------------------------------------------------------------------------------------------
Project::~Project()
{
	DeleteGraph(m_backGroundDraw);
	DeleteGraph(m_charaDraw);
	DeleteGraph(m_underGroundDraw);
	DeleteGraph(m_vChipDraw);
	std::vector<int>().swap(m_vChipAreaX);
	std::vector<int>().swap(m_vChipAreaY);
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::Draw()
{
	// �Q�[��
	GameDraw();

	SpeedManageDraw();

	// �O���b�h
	GridDraw();

	// �}�E�X
	MouseDraw();
}



/// ---------------------------------------------------------------------------------------------------------------------
void Project::Process()
{
	// �}�E�X�̈ʒu���擾����
	m_mouseAreaX = MouseData::GetMouseArea().x + m_areaX - 1920;


	// �Z�[�u����
	if (KeyData::Get(KEY_INPUT_P) == 1)
	{
		TextOutPut();
	}


	// �X�N���[��
	SideScrollProcess();


	// �h�b�g�O���b�h
	GridProcess();


	// �`�b�v
	ChipProcess();
}