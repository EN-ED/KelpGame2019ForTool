#pragma once
#include <string>
#include <vector>
#include <map>
#include "Character.hpp"
#include "Garbage.hpp"
#include "BlurScreen.hpp"
#include "BackGround.hpp"
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include "DxLib.h"
#include "BlurScreen.hpp"

#include <random>
#include <fstream>
#include <sstream>
#include <iostream>


class DragProject
{
private:
	// 座標をセーブする
	void TextOutPut();

	// 画面上マウス座標
	int m_mouseAreaX;

	// チップ配置座標
	std::vector<int> m_vChipAreaX;
	std::vector<int> m_vChipAreaY;


	void GameDraw();

	void MouseDraw();


	void ChipProcess();


	BackGround* mp_backGround;
	Character* mp_character;

	bool m_isFirstSpeedUp;

	std::vector<Garbage*> mp_garbage;

	int m_vChipDraw[3];
	int m_nowSelectChip;
	std::vector<int> m_vChipID;

	bool m_gameStop;

	int m_scroll;

	bool m_6speedGame;

	bool m_8speedGame;

	bool m_4speedGame;

	bool m_2speedGame;

	void Load(std::string str);


public:
	DragProject(std::string str);
	~DragProject();


	void Draw();
	void Process();
};

