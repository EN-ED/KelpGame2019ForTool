#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


class MainProject
{
private:
	// 座標をセーブする
	void TextOutPut();

	// マウスをクリックしているかどうか
	int m_isMouseClick;

	// スクロール座標
	int m_scrollX;

	// スクロールスピード
	int m_scrollSpeed;


	/// --------------------------------------------------
	// 背景画像
	int m_backGroundDraw;


	/// --------------------------------------------------
	// キャラクターコマの総枚数
	const int m_charaNum = 20;

	// キャラクター画像
	int m_charaDraw[20];

	// キャラクターの座標
	int m_charaAreaX;

	// キャラクターを動かしている最中かどうか
	int m_isClickChara;

	// 画像モーション速度
	const int m_playerDrawAnimSpeed = 6;
	int m_playerDrawAnimCount;


	/// --------------------------------------------------
	// 追いかけるものの画像
	int m_chaserDraw[31];

	// 追いかけるもののコマの総枚数
	const int m_chaserNum = 31;

	// 追いかけるものの座標
	int m_chaserAreaX;

	// 追いかけるものを動かしている最中かどうか
	int m_isClickChaser;

	// 画像モーション速度
	int m_chaserSpeedCount;
	const int m_chasrArraySpeed = 2;


	/// --------------------------------------------------
	// 地面の画像
	int m_underGroundDraw;


	int m_saveCount;


public:
	MainProject();
	~MainProject();


	void Draw();
	void Process();
};

