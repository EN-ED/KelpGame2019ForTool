#pragma once
#include <string>
#include <vector>
#include <map>


class Project
{
private:
	// ���W���Z�[�u����
	void TextOutPut();

	// �X�N���[�����W
	int m_scrollX;

	// �����W
	int m_areaX;

	// ��ʏ�}�E�X���W
	int m_mouseAreaX;

	// �X�N���[���X�s�[�h
	int m_scrollSpeed;

	// 32�h�b�g�O���b�h�\�����邩�ǂ���
	bool m_is32DotGrid;

	// 64�h�b�g�O���b�h�\�����邩�ǂ���
	bool m_is64DotGrid;

	// 96�h�b�g�O���b�h�\�����邩�ǂ���
	bool m_is96DotGrid;


	/// --------------------------------------------------
	// �w�i�摜
	int m_backGroundDraw;


	/// --------------------------------------------------
	// �L�����N�^�[�摜
	int m_charaDraw;


	/// --------------------------------------------------
	// �n�ʂ̉摜
	int m_underGroundDraw;


	/// ---------------------------------------------------
	// �G�f�B�^�`�b�v�摜
	int m_vChipDraw;

	// �`�b�v�z�u���W
	std::vector<int> m_vChipAreaX;
	std::vector<int> m_vChipAreaY;


	void GameDraw();

	void GridDraw();

	void MouseDraw();

	void SpeedManageDraw();


	void SideScrollProcess();

	void GridProcess();

	void ChipProcess();


public:
	Project();
	~Project();


	void Draw();
	void Process();
};

