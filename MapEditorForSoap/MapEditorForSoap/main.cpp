#include "Project.hpp"
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include "DxLib.h"
#include "DragProject.hpp"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("MapEditorForSoap");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(255, 255, 255);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth, winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetAlwaysRunFlag(TRUE);			// ���ł��A�N�e�B�u�ɂ���
	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(TRUE);			// �}�E�X�J�[�\����\������
	SetDragFileValidFlag(TRUE);		// �h���b�O�A���h�h���b�v�ǉ�����悤�ɒ���


	Project project = Project();
	SetKeyInputCursorBrinkFlag(TRUE);


	MouseData::UpDate();

	DragProject* pproject = nullptr;

	bool flag = false;

	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd())
	{
		MouseData::UpDate();
		KeyData::UpDate();

		// �h���b�O�A���h�h���b�v���s��ꂽ�Ƃ�
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// �t�@�C���̃p�X���������鉼�u���ϐ�

			GetDragFilePath(filePath);				// �h���b�O�A���h�h���b�v�̃p�X���擾

			pproject = new DragProject(filePath);
			flag = true;
		}

		if (flag)
		{
			pproject->Draw();
			pproject->Process();
		}
		else
		{
			project.Draw();
			project.Process();
		}
	}


	// ��Еt��
	if (flag)
	{
		delete pproject;
	}
	InitGraph();
	DxLib_End();


	// �v���W�F�N�g�I��
	return 0;
}