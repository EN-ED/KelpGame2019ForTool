#include "MainProject.hpp"



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::TextRead()
{
	// 行確認用変数
	int readCount = 0;

	// ファイルを読み込む
	std::ifstream readFile("media\\text.csv");

	// 行を取得する
	std::string readLine = "";


	// ファイル読み込み失敗
	if (readFile.fail())
	{
		return;
	}


	// 行ずつ確認
	while (getline(readFile, readLine))
	{
		std::string token;
		std::istringstream stream(readLine);

		// マップデータ多めに作成
		int tempReadCount = readCount + 1;
		vv_csvData.resize(tempReadCount);

		// [,]まで確認
		while (std::getline(stream, token, ','))
		{
			// マップデータに追加
			vv_csvData[readCount].push_back(token);
		}

		// 行を加算
		readCount++;
	}


	// ファイルを閉じる
	readFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::TextOutPut()
{
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand(10000, 99999);        // [0, 99] 範囲の一様乱数
	std::string randStr = "media\\Save\\" + std::to_string(rand(mt)) + ".csv";
	// ファイルを読み込む
	std::ofstream saveFile(randStr.c_str());


	// ファイル読み込み失敗
	if (saveFile.fail())
	{
		return;
	}


	saveFile << "キャラクター" << "," << m_charaAreaX << std::endl << "速度詳細XxY" << "," << m_fasterAreaX << "," << m_fasterAreaY << std::endl;


	// ファイルを閉じる
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------
MainProject::MainProject()
{
	// CSVデータ受け渡し
	vv_csvData.clear();

	TextRead();

	std::string mediaStr = "media\\";
	std::string addStr = "";


	// 背景
	addStr = mediaStr + vv_csvData[0][1].c_str();
	m_backGroundDraw	 = LoadGraph(addStr.c_str());

	m_scrollX = 0;
	m_isScroll = false;


	// キャラクター
	m_charaXNum			 = atoi(vv_csvData[1][1].c_str());

	m_charaXSize		 = atoi(vv_csvData[2][1].c_str());

	m_charaYNum			 = atoi(vv_csvData[3][1].c_str());

	m_charaYSize		 = atoi(vv_csvData[4][1].c_str());

	m_charaNum			 = atoi(vv_csvData[5][1].c_str());
	
	addStr = "";
	addStr = mediaStr + vv_csvData[6][1].c_str();
	LoadDivGraph(addStr.c_str(), m_charaNum, m_charaXNum, m_charaYNum, m_charaXSize, m_charaYSize, m_charaDraw);
	m_charaAreaX = 980;


	// 追いかけるもの
	m_chaserXNum = atoi(vv_csvData[7][1].c_str());

	m_chaserXSize = atoi(vv_csvData[8][1].c_str());

	m_chaserYNum = atoi(vv_csvData[9][1].c_str());

	m_chaserYSize = atoi(vv_csvData[10][1].c_str());

	m_chaserNum = atoi(vv_csvData[11][1].c_str());

	addStr = "";
	addStr = mediaStr + vv_csvData[12][1].c_str();
	LoadDivGraph(addStr.c_str(), m_chaserNum, m_chaserXNum, m_chaserYNum, m_chaserXSize, m_chaserYSize, m_chaserDraw);


	// 障害物
	addStr = "";
	addStr = mediaStr + vv_csvData[13][1].c_str();
	m_garbageDraw		 = LoadGraph(addStr.c_str());
	GetGraphSize(m_garbageDraw, &m_garbageXSize, &m_garbageYSize);


	// 地面
	addStr = "";
	addStr = mediaStr + vv_csvData[14][1].c_str();
	m_underGroundDraw	 = LoadGraph(addStr.c_str());
	GetGraphSize(m_underGroundDraw, &m_underGroundXSize, &m_underGroundYSize);


	// 速度詳細
	addStr = "";
	addStr = mediaStr + vv_csvData[15][1].c_str();
	m_fasterDraw		 = LoadGraph(addStr.c_str());
	GetGraphSize(m_fasterDraw, &m_fasterXSize, &m_fasterYSize);
	m_fasterAreaX = 1920 - m_fasterXSize - 128;
	m_fasterAreaY = 128;


	// マウス
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
	// 背景
	DrawGraph(m_scrollX, 0, m_backGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 0, m_backGroundDraw, true);

	// 地面
	DrawGraph(m_scrollX, 1080 - m_underGroundYSize, m_underGroundDraw, true);
	DrawGraph(m_scrollX + 1920, 1080 - m_underGroundYSize, m_underGroundDraw, true);

	// 追いかけるもの
	DrawGraph(0, 1080 - m_underGroundYSize - m_chaserYSize, m_chaserDraw[0], true);

	// キャラクター
	DrawGraph(m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize, m_charaDraw[0], true);
	DrawFormatString(m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize - 20, GetColor(0, 0, 0), "%d x %d", m_charaAreaX, 1080 - m_underGroundYSize - m_charaYSize);

	// 障害物
	DrawGraph(980 + 490, 1080 - m_underGroundYSize - m_garbageYSize, m_garbageDraw, true);

	// 速度詳細
	DrawGraph(m_fasterAreaX, m_fasterAreaY, m_fasterDraw, true);
	DrawFormatString(m_fasterAreaX, m_fasterAreaY + m_fasterYSize, GetColor(0, 0, 0), "%d x %d : speed %d", m_fasterAreaX, m_fasterAreaY, m_scrollSpeed);

	// マウス
	DrawFormatString(m_mouseX, m_mouseY, GetColor(0, 0, 0), "%d x %d", m_mouseX, m_mouseY);

	// 操作
	DrawFormatString(10, 0, GetColor(0, 0, 0), "Zキー：速度アップ\nXキー：速度ダウン\nCキー：速度停止\nWASDキー：速度表示座標移動\n矢印右左：キャラクター座標移動\nキャラクターと速度表示はマウスによる移動可\nBキー：座標保存CSV出力\nMキー：座標リセット");
}



/// ---------------------------------------------------------------------------------------------------------------------
void MainProject::Process()
{
	// マウスの位置を取得する
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



	// 位置を初期化する
	if (KeyData::Get(KEY_INPUT_M) == 1)
	{
		m_charaAreaX = 980;
		m_fasterAreaX = 1920 - m_fasterXSize - 128;
		m_fasterAreaY = 128;
		m_isScroll = false;
		m_scrollSpeed = 0;
		m_scrollX = 0;
	}


	// セーブする
	if (KeyData::Get(KEY_INPUT_B) == 1)
	{
		TextOutPut();
	}


	// 速度詳細の座標を動かす
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
	// マウス
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


	// キャラクターの座標を動かす
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


	// スクロールさせる
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
