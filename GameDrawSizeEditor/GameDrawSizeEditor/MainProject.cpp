#include "MainProject.hpp"



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::TextRead()
{
	// �s�m�F�p�ϐ�
	int readCount = 0;

	// �t�@�C����ǂݍ���
	std::ifstream readFile("media\\text.csv");

	// �s���擾����
	std::string readLine = "";


	// �t�@�C���ǂݍ��ݎ��s
	if (readFile.fail())
	{
		return;
	}


	// �s���m�F
	while (getline(readFile, readLine))
	{
		std::string token;
		std::istringstream stream(readLine);

		// �}�b�v�f�[�^���߂ɍ쐬
		int tempReadCount = readCount + 1;
		vv_csvData.resize(tempReadCount);

		// [,]�܂Ŋm�F
		while (std::getline(stream, token, ','))
		{
			// �}�b�v�f�[�^�ɒǉ�
			vv_csvData[readCount].push_back(token);
		}

		// �s�����Z
		readCount++;
	}


	// �t�@�C�������
	readFile.close();
}



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


	saveFile << "�L�����N�^�[" << "," << m_charaAreaX << std::endl << "���x�ڍ�XxY" << "," << m_fasterAreaX << "," << m_fasterAreaY << std::endl;


	// �t�@�C�������
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------
MainProject::MainProject()
{
	// CSV�f�[�^�󂯓n��
	vv_csvData.clear();

	TextRead();

	std::string mediaStr = "media\\";
	std::string addStr = "";


	// �w�i
	addStr = mediaStr + vv_csvData[0][1].c_str();
	m_backGroundDraw	 = LoadGraph(addStr.c_str());

	m_scrollX = 0;
	m_isScroll = false;


	// �L�����N�^�[
	m_charaXNum			 = atoi(vv_csvData[1][1].c_str());

	m_charaXSize		 = atoi(vv_csvData[2][1].c_str());

	m_charaYNum			 = atoi(vv_csvData[3][1].c_str());

	m_charaYSize		 = atoi(vv_csvData[4][1].c_str());

	m_charaNum			 = atoi(vv_csvData[5][1].c_str());
	
	addStr = "";
	addStr = mediaStr + vv_csvData[6][1].c_str();
	LoadDivGraph(addStr.c_str(), m_charaNum, m_charaXNum, m_charaYNum, m_charaXSize, m_charaYSize, m_charaDraw);
	m_charaAreaX = 980;


	// �ǂ����������
	m_chaserXNum = atoi(vv_csvData[7][1].c_str());

	m_chaserXSize = atoi(vv_csvData[8][1].c_str());

	m_chaserYNum = atoi(vv_csvData[9][1].c_str());

	m_chaserYSize = atoi(vv_csvData[10][1].c_str());

	m_chaserNum = atoi(vv_csvData[11][1].c_str());

	addStr = "";
	addStr = mediaStr + vv_csvData[12][1].c_str();
	LoadDivGraph(addStr.c_str(), m_chaserNum, m_chaserXNum, m_chaserYNum, m_chaserXSize, m_chaserYSize, m_chaserDraw);


	// ��Q��
	addStr = "";
	addStr = mediaStr + vv_csvData[13][1].c_str();
	m_garbageDraw		 = LoadGraph(addStr.c_str());
	GetGraphSize(m_garbageDraw, &m_garbageXSize, &m_garbageYSize);


	// �n��
	addStr = "";
	addStr = mediaStr + vv_csvData[14][1].c_str();
	m_underGroundDraw	 = LoadGraph(addStr.c_str());
	GetGraphSize(m_underGroundDraw, &m_underGroundXSize, &m_underGroundYSize);


	// ���x�ڍ�
	addStr = "";
	addStr = mediaStr + vv_csvData[15][1].c_str();
	m_fasterDraw		 = LoadGraph(addStr.c_str());
	GetGraphSize(m_fasterDraw, &m_fasterXSize, &m_fasterYSize);
	m_fasterAreaX = 1920 - m_fasterXSize - 128;
	m_fasterAreaY = 128;


	// �}�E�X
	GetMousePoint(&m_mouseX, &m_mouseY);
	m_preMouseX = m_mouseX;
	m_preMouseY = m_mouseY;
	m_isMouseClick = false;
	m_isClickChara = false;
	m_isClickFaster = false;
}



/// ---------------------------------------------------------------------------------------------------------------------
MainProject::~MainProject()
{
	std::vector<std::vector<std::string>>().swap(vv_csvData);
	DeleteGraph(m_backGroundDraw);
	for (int i = 0; i != m_charaNum; ++i)
	{
		DeleteGraph(m_charaDraw[i]);
	}
	for (int i = 0; i != m_chaserNum; ++i)
	{
		DeleteGraph(m_chaserDraw[i]);
	}
	DeleteGraph(m_garbageDraw);
	DeleteGraph(m_underGroundDraw);
	DeleteGraph(m_fasterDraw);
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::Draw()
{
	// �w�i
	DrawGraph(m_scrollX, 0, m_backGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 0, m_backGroundDraw, true);

	// �n��
	DrawGraph(m_scrollX, 1080 - m_underGroundYSize, m_underGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 1080 - m_underGroundYSize, m_underGroundDraw, true);

	// �ǂ����������
	DrawGraph(0, 1080 - m_underGroundYSize - m_chaserYSize, m_chaserDraw[0], true);

	// �L�����N�^�[
	DrawGraph(m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize, m_charaDraw[0], true);
	DrawFormatString(m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize - 20, GetColor(0, 0, 0), "%d x %d", m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize);

	// ��Q��
	DrawGraph(980 + 490, 1080 - m_underGroundYSize - m_garbageYSize, m_garbageDraw, true);

	// ���x�ڍ�
	DrawGraph(m_fasterAreaX, m_fasterAreaY, m_fasterDraw, true);
	DrawFormatString(m_fasterAreaX, m_fasterAreaY + m_fasterYSize, GetColor(0, 0, 0), "%d x %d : speed %d", m_fasterAreaX, m_fasterAreaY, m_scrollSpeed);

	// �}�E�X
	DrawFormatString(m_mouseX, m_mouseY, GetColor(0, 0, 0), "%d x %d", m_mouseX, m_mouseY);

	// ����
	DrawFormatString(10, 0, GetColor(0, 0, 0), "Z�L�[�F���x�A�b�v\nX�L�[�F���x�_�E��\nC�L�[�F���x��~\nWASD�L�[�F���x�\�����W�ړ�\n���E���F�L�����N�^�[���W�ړ�\n�L�����N�^�[�Ƒ��x�\���̓}�E�X�ɂ��ړ���\nB�L�[�F���W�ۑ�CSV�o��\nM�L�[�F���W���Z�b�g");
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::Process()
{
	// �}�E�X�̈ʒu���擾����
	m_preMouseX = m_mouseX;
	m_preMouseY = m_mouseY;
	GetMousePoint(&m_mouseX, &m_mouseY);
	if (MouseData::GetClick(static_cast<int>(CLICK::LEFT)) >= 1)
	{
		m_isMouseClick = true;
	}
	else
	{
		m_isMouseClick = false;
		m_isClickChara = false;
		m_isClickFaster = false;
	}



	// �ʒu������������
	if (KeyData::Get(KEY_INPUT_M) == 1)
	{
		m_charaAreaX = 980;
		m_fasterAreaX = 1920 - m_fasterXSize - 128;
		m_fasterAreaY = 128;
		m_isScroll = false;
		m_scrollSpeed = 0;
		m_scrollX = 0;
	}


	// �Z�[�u����
	if (KeyData::Get(KEY_INPUT_B) == 1)
	{
		TextOutPut();
	}


	// ���x�ڍׂ̍��W�𓮂���
	if (KeyData::Get(KEY_INPUT_W) == 1)
	{
		m_fasterAreaY--;
	}
	if (KeyData::Get(KEY_INPUT_S) == 1)
	{
		m_fasterAreaY++;
	}
	if (KeyData::Get(KEY_INPUT_A) == 1)
	{
		m_fasterAreaX--;
	}
	if (KeyData::Get(KEY_INPUT_D) == 1)
	{
		m_fasterAreaX++;
	}
	// �}�E�X
	if (m_isMouseClick && !m_isClickChara)
	{
		if (m_mouseX > m_fasterAreaX
			&& m_mouseX < m_fasterAreaX + m_fasterXSize
			&& m_mouseY > m_fasterAreaY
			&& m_mouseY < m_fasterAreaY + m_fasterYSize)
		{
			m_isClickFaster = true;
		}
		if (m_isClickFaster)
		{
			m_fasterAreaX += (m_mouseX - m_preMouseX);
			m_fasterAreaY += (m_mouseY - m_preMouseY);
		}
	}


	// �L�����N�^�[�̍��W�𓮂���
	if (KeyData::Get(KEY_INPUT_RIGHT) == 1)
	{
		m_charaAreaX++;
	}
	if (KeyData::Get(KEY_INPUT_LEFT) == 1)
	{
		m_charaAreaX--;
	}
	if (m_isMouseClick && !m_isClickFaster)
	{
		if (m_mouseX > m_charaAreaX
			&& m_mouseX < m_charaAreaX + m_fasterXSize
			&& m_mouseY >  1080 - m_underGroundYSize - m_charaYSize
			&& m_mouseY < 1080 - m_underGroundYSize)
		{
			m_isClickChara = true;
		}
		if (m_isClickChara)
		{
			m_charaAreaX += (m_mouseX - m_preMouseX);
		}
	}


	// �X�N���[��������
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		if (!m_isScroll) m_isScroll = true;
		m_scrollSpeed++;
	}
	if (KeyData::Get(KEY_INPUT_X) == 1 && m_scrollSpeed != 0)
	{
		m_scrollSpeed--;
	}
	if (KeyData::Get(KEY_INPUT_C) == 1)
	{
		m_isScroll = false;
	}
	if (m_isScroll)
	{
		m_scrollX -= m_scrollSpeed;
		if (m_scrollX <= -1920)
		{
			m_scrollX = 0;
		}
	}
}
