#include "DragProject.hpp"



/// ---------------------------------------------------------------------------------------------------------------------
BlurScreen gg_blurScreen;



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::TextOutPut()
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


	for (int i = 0; i != m_vChipAreaX.size(); ++i)
	{
		saveFile << m_vChipAreaX.at(i) << "," << m_vChipAreaY.at(i) << "," << m_vChipID.at(i) << std::endl;
	}


	// ファイルを閉じる
	saveFile.close();
}



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::GameDraw()
{
	if (mp_character->GetIsSpeedUp())
	{
		if (m_isFirstSpeedUp)
		{
			gg_blurScreen.PreRenderBlurScreen();
			mp_backGround->Draw();
			mp_character->BlurDraw();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->Draw();
			}
			gg_blurScreen.PostRenderBlurScreen();

			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->Draw();
			}
			mp_character->Draw();
		}
		else
		{
			m_isFirstSpeedUp = true;
			gg_blurScreen.ReplayInit();
			gg_blurScreen.PreRenderBlurScreen();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->Draw();
			}
			mp_backGround->Draw();
			mp_character->BlurDraw();
			gg_blurScreen.PostRenderBlurScreen();

			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->Draw();
			}
			mp_character->Draw();
		}
	}
	else
	{
		mp_backGround->Draw();
		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			mp_garbage[i]->Draw();
		}
		mp_character->Draw();
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::MouseDraw()
{
	// チップ
	DrawGraph(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, m_vChipDraw[m_nowSelectChip], true);

	// マウス
	DrawFormatString(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, GetColor(0, 0, 0), "%d x %d", m_mouseAreaX, MouseData::GetMouseArea().y);
}



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::ChipProcess()
{
	// チップ配置
	if (MouseData::GetMouseArea().y < 1080 - 128)
	{
		if (MouseData::GetClick(MouseData::ECLICK::LEFT) == 1)
		{
			m_vChipAreaX.push_back(m_mouseAreaX);
			m_vChipAreaY.push_back(MouseData::GetMouseArea().y);
			m_vChipID.push_back(m_nowSelectChip);
			mp_garbage.push_back(new Garbage(MouseData::GetMouseArea().x, MouseData::GetMouseArea().y, static_cast<Garbage::EDrawID>(m_nowSelectChip)));
		}
	}


	// チップ削除
	if (MouseData::GetClick(MouseData::ECLICK::RIGHT) == 1)
	{
		for (int i = 0; i != m_vChipAreaX.size(); ++i)
		{
			if (MouseData::GetMouseArea().x > mp_garbage[i]->GetX() && MouseData::GetMouseArea().x < mp_garbage[i]->GetX() + 256
				&& MouseData::GetMouseArea().y > mp_garbage[i]->GetY() && MouseData::GetMouseArea().y < mp_garbage[i]->GetY() + 256)
			{
				m_vChipAreaX.erase(m_vChipAreaX.begin() + i);
				m_vChipAreaY.erase(m_vChipAreaY.begin() + i);
				delete mp_garbage[i];
				mp_garbage.erase(mp_garbage.begin() + i);
				break;
			}
		}
	}


	if (MouseData::GetClick(MouseData::ECLICK::CENTER) == 1)
	{
		if (++m_nowSelectChip >= 3) m_nowSelectChip = 0;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------
DragProject::DragProject(std::string str)
{
	std::vector<int>().swap(m_vChipAreaX);
	std::vector<int>().swap(m_vChipAreaY);
	std::vector<int>().swap(m_vChipID);




	mp_backGround = nullptr;
	mp_backGround = new BackGround();

	mp_character = nullptr;
	mp_character = new Character();

	gg_blurScreen.Init(200, 6, -2, 0, 0);

	m_isFirstSpeedUp = false;


	std::vector<Garbage*>().swap(mp_garbage);

	m_nowSelectChip = 0;
	m_vChipDraw[0] = LoadGraph("media\\item\\Doro.png");
	m_vChipDraw[1] = LoadGraph("media\\item\\mizutamari.png");
	m_vChipDraw[2] = LoadGraph("media\\item\\Sekiyu.png");

	m_gameStop = false;

	// マウス
	m_mouseAreaX = MouseData::GetMouseArea().x + mp_backGround->GetAllAreaX();

	m_scroll = 0;

	m_6speedGame = false;
	m_8speedGame = false;
	m_4speedGame = false;
	m_2speedGame = false;


	Load(str);
}



/// ---------------------------------------------------------------------------------------------------------------------
DragProject::~DragProject()
{
	DeleteGraph(m_vChipDraw[0]);
	DeleteGraph(m_vChipDraw[1]);
	DeleteGraph(m_vChipDraw[2]);

	std::vector<int>().swap(m_vChipAreaX);
	std::vector<int>().swap(m_vChipAreaY);
	std::vector<int>().swap(m_vChipID);


	for (int i = 0; i != mp_garbage.size(); ++i)
	{
		if (mp_garbage[i] != nullptr) delete mp_garbage[i];
	}
	if (mp_character != nullptr) delete mp_character;
	if (mp_backGround != nullptr) delete mp_backGround;

	gg_blurScreen.Release();
	gg_blurScreen.~BlurScreen();
}



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::Draw()
{
	// ゲーム
	GameDraw();

	// マウス
	MouseDraw();
}



/// ---------------------------------------------------------------------------------------------------------------------
void DragProject::Process()
{
	// マウスの位置を取得する
	m_mouseAreaX = MouseData::GetMouseArea().x + mp_backGround->GetAllAreaX();


	// セーブする
	if (KeyData::Get(KEY_INPUT_P) == 1)
	{
		TextOutPut();
	}


	if (KeyData::Get(KEY_INPUT_RIGHT) > 1)
	{
		mp_backGround->SetMoveX(10, true);
		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			mp_garbage[i]->SetMoveX(10, true);
		}
	}
	if (KeyData::Get(KEY_INPUT_LEFT) > 1)
	{
		if (mp_backGround->GetArea() > 0)
		{
			mp_backGround->SetMoveX(10, false);
			mp_backGround->Process();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->SetMoveX(10, false);
			}
		}
	}

	if (KeyData::Get(KEY_INPUT_R) == 1)
	{
		mp_character->SetReset();
		mp_backGround->SetReset();
		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			mp_garbage[i]->SetReset(m_vChipAreaX[i], m_vChipAreaY[i]);
		}
		m_8speedGame = false;
		m_6speedGame = false;
		m_4speedGame = false;
		m_2speedGame = false;
		m_gameStop = false;
	}

	if (KeyData::Get(KEY_INPUT_S) == 1 && !m_gameStop && !m_6speedGame && !m_4speedGame && !m_2speedGame)
	{
		if (!m_8speedGame)
		{
			mp_character->SetReset();
			mp_backGround->SetReset();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->SetReset(m_vChipAreaX[i], m_vChipAreaY[i]);
			}
			m_8speedGame = true;
		}
		else
		{
			m_8speedGame = false;
		}
	}

	if (KeyData::Get(KEY_INPUT_D) == 1 && !m_gameStop && !m_8speedGame && !m_4speedGame && !m_2speedGame)
	{
		if (!m_6speedGame)
		{
			mp_character->SetReset();
			mp_backGround->SetReset();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->SetReset(m_vChipAreaX[i], m_vChipAreaY[i]);
			}
			m_6speedGame = true;
		}
		else
		{
			m_6speedGame = false;
		}
	}

	if (KeyData::Get(KEY_INPUT_F) == 1 && !m_gameStop && !m_8speedGame && !m_6speedGame && !m_2speedGame)
	{
		if (!m_4speedGame)
		{
			mp_character->SetReset();
			mp_backGround->SetReset();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->SetReset(m_vChipAreaX[i], m_vChipAreaY[i]);
			}
			m_4speedGame = true;
		}
		else
		{
			m_4speedGame = false;
		}
	}

	if (KeyData::Get(KEY_INPUT_G) == 1 && !m_gameStop && !m_8speedGame && !m_4speedGame && !m_6speedGame)
	{
		if (!m_2speedGame)
		{
			mp_character->SetReset();
			mp_backGround->SetReset();
			for (int i = 0; i != mp_garbage.size(); ++i)
			{
				mp_garbage[i]->SetReset(m_vChipAreaX[i], m_vChipAreaY[i]);
			}
			m_2speedGame = true;
		}
		else
		{
			m_2speedGame = false;
		}
	}


	if (KeyData::Get(KEY_INPUT_NUMPADENTER) == 1 && !m_8speedGame && !m_6speedGame && !m_4speedGame && !m_2speedGame)
	{
		m_gameStop = !m_gameStop;
	}


	if (m_gameStop)
	{
		// チップ
		ChipProcess();


		mp_backGround->Process();


		mp_character->Process();


		mp_backGround->SetSpeed(mp_character->GetSpeed());


		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			if (mp_character->GetIsSpeedUp())
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
				continue;
			}
			else
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
			}
			if (/*石鹸の右端 が 障害物の左端 より大きい*/
				mp_character->GetAreaX() + mp_character->GetSize() >= mp_garbage[i]->GetX()
				/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
				&& mp_character->GetAreaX() <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
				/*石鹸の下端 が 障害物の上端 より大きい*/
				&& mp_character->GetAreaY() + mp_character->GetSize() >= mp_garbage[i]->GetY()
				/*石鹸の上端 が 障害物の下端 より小さい*/
				&& mp_character->GetAreaY() <= mp_garbage[i]->GetY() + 256)
			{
				mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}
		}
	}
	else if (m_8speedGame)
	{
		mp_backGround->Process();


		mp_character->Process();


		mp_backGround->SetSpeed(mp_character->GetSpeed());


		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			if (mp_character->GetIsSpeedUp())
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
				continue;
			}
			else
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.8f));
			}
			if (/*石鹸の右端 が 障害物の左端 より大きい*/
				mp_character->GetAreaX() + mp_character->GetSize() >= mp_garbage[i]->GetX()
				/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
				&& mp_character->GetAreaX() <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
				/*石鹸の下端 が 障害物の上端 より大きい*/
				&& mp_character->GetAreaY() + mp_character->GetSize() >= mp_garbage[i]->GetY()
				/*石鹸の上端 が 障害物の下端 より小さい*/
				&& mp_character->GetAreaY() <= mp_garbage[i]->GetY() + 256)
			{
				mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}
		}
	}
	else if (m_6speedGame)
	{
		mp_backGround->Process();


		mp_character->Process();


		mp_backGround->SetSpeed(mp_character->GetSpeed());


		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			if (mp_character->GetIsSpeedUp())
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
				continue;
			}
			else
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.6f));
			}
			if (/*石鹸の右端 が 障害物の左端 より大きい*/
				mp_character->GetAreaX() + mp_character->GetSize() >= mp_garbage[i]->GetX()
				/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
				&& mp_character->GetAreaX() <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
				/*石鹸の下端 が 障害物の上端 より大きい*/
				&& mp_character->GetAreaY() + mp_character->GetSize() >= mp_garbage[i]->GetY()
				/*石鹸の上端 が 障害物の下端 より小さい*/
				&& mp_character->GetAreaY() <= mp_garbage[i]->GetY() + 256)
			{
				mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}
		}
	}
	else if (m_4speedGame)
	{
		mp_backGround->Process();


		mp_character->Process();


		mp_backGround->SetSpeed(mp_character->GetSpeed());


		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			if (mp_character->GetIsSpeedUp())
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
				continue;
			}
			else
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.4f));
			}
			if (/*石鹸の右端 が 障害物の左端 より大きい*/
				mp_character->GetAreaX() + mp_character->GetSize() >= mp_garbage[i]->GetX()
				/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
				&& mp_character->GetAreaX() <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
				/*石鹸の下端 が 障害物の上端 より大きい*/
				&& mp_character->GetAreaY() + mp_character->GetSize() >= mp_garbage[i]->GetY()
				/*石鹸の上端 が 障害物の下端 より小さい*/
				&& mp_character->GetAreaY() <= mp_garbage[i]->GetY() + 256)
			{
				mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}
		}
	}
	else if (m_2speedGame)
	{
		mp_backGround->Process();


		mp_character->Process();


		mp_backGround->SetSpeed(mp_character->GetSpeed());


		for (int i = 0; i != mp_garbage.size(); ++i)
		{
			if (mp_garbage[i]->GetX() + 256 < 0) continue;
			if (mp_character->GetIsSpeedUp())
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed()));
				continue;
			}
			else
			{
				mp_garbage[i]->Process(static_cast<int>(mp_character->GetSpeed() * 0.2f));
			}
			if (/*石鹸の右端 が 障害物の左端 より大きい*/
				mp_character->GetAreaX() + mp_character->GetSize() >= mp_garbage[i]->GetX()
				/*石鹸の左端 が 障害物の左端と障害物の速度 より小さい*/
				&& mp_character->GetAreaX() <= mp_garbage[i]->GetX() + static_cast<int>(mp_character->GetSpeed() * 0.25f)
				/*石鹸の下端 が 障害物の上端 より大きい*/
				&& mp_character->GetAreaY() + mp_character->GetSize() >= mp_garbage[i]->GetY()
				/*石鹸の上端 が 障害物の下端 より小さい*/
				&& mp_character->GetAreaY() <= mp_garbage[i]->GetY() + 256)
			{
				mp_character->HitGarbageNow(i, static_cast<Character::EHitGarbageID>(mp_garbage[i]->GetID()));
			}
		}
	}
	else
	{
		// チップ
		ChipProcess();
	}
}

void DragProject::Load(std::string strr)
{
	std::ifstream ifs;
	std::vector<std::vector<std::string>> mapdata;
	ifs.open(strr);
	// マップデータ読み込み失敗
	if (ifs.fail())
	{
		std::cerr << "LoadError" << std::endl;
	}

	// 仮置き
	std::string str;
	int count = 0;

	while (getline(ifs, str))
	{
		// 仮置き
		std::string token;
		std::istringstream stream(str);

		// メモリ確保
		mapdata.resize(count + 1);

		while (getline(stream, token, ','))
		{
			mapdata[count].push_back(token);
		}
		// カウントアップ
		count++;
	}

	for (int i = 0, n = mapdata.size(); i != n; ++i)
	{
		m_vChipAreaX.push_back(std::stoi(mapdata[i][0].c_str()));
		m_vChipAreaY.push_back(std::stoi(mapdata[i][1].c_str()));
		m_vChipID.push_back(std::stoi(mapdata[i][2].c_str()));
	}

	for (int i = 0, n = m_vChipAreaX.size(); i != n; ++i)
	{
		mp_garbage.push_back(new Garbage(m_vChipAreaX.at(i), m_vChipAreaY.at(i), static_cast<Garbage::EDrawID>(m_vChipID.at(i))));
	}
	mp_garbage.push_back(new Garbage(1920, 0, Garbage::EDrawID::doro));
}
