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
	// csvデータの読み込み
	void TextRead();

	// csvデータを保存する
	std::vector<std::vector<std::string>> vv_csvData;

	// 座標をセーブする
	void TextOutPut();
	
	// マウスの位置
	int m_mouseX, m_mouseY;

	// 直前のマウスの位置
	int m_preMouseX, m_preMouseY;

	// マウスをクリックしているかどうか
	int m_isMouseClick;

	// スクロール座標
	int m_scrollX;

	// スクロールスピード
	int m_scrollSpeed;

	// スクロールさせるかどうか
	int m_isScroll;


	/// --------------------------------------------------
	// 背景画像
	int m_backGroundDraw;


	/// --------------------------------------------------
	// キャラクターコマの枚数
	int m_charaXNum, m_charaYNum;

	// キャラクターコマのサイズ
	int m_charaXSize, m_charaYSize;

	// キャラクターコマの総枚数
	int m_charaNum;

	// キャラクター画像
	int m_charaDraw[64];

	// キャラクターの座標
	int m_charaAreaX;

	// キャラクターを動かしている最中かどうか
	int m_isClickChara;


	/// --------------------------------------------------
	// 追いかけるものの画像
	int m_chaserDraw[64];

	// 追いかけるものの画像サイズ
	int m_chaserXSize, m_chaserYSize;

	// 追いかけるもののコマの枚数
	int m_chaserXNum, m_chaserYNum;

	// 追いかけるもののコマの総枚数
	int m_chaserNum;


	/// --------------------------------------------------
	// 障害物の画像
	int m_garbageDraw;

	// 障害物の画像サイズ
	int m_garbageXSize, m_garbageYSize;


	/// --------------------------------------------------
	// 地面の画像
	int m_underGroundDraw;

	// 地面の画像サイズ
	int m_underGroundXSize, m_underGroundYSize;


	/// --------------------------------------------------
	// 速度経過の画像
	int m_fasterDraw;

	// 速度経過の画像サイズ
	int m_fasterXSize, m_fasterYSize;

	// 速度経過の座標
	int m_fasterAreaX, m_fasterAreaY;

	// 速度経過を動かしている最中かどうか
	int m_isClickFaster;


public:
	MainProject();
	~MainProject();


	void Draw();
	void Process();
};

