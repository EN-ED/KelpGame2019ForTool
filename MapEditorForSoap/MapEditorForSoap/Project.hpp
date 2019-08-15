#pragma once
#include <string>
#include <vector>
#include <map>


class Project
{
private:
	// 座標をセーブする
	void TextOutPut();

	// スクロール座標
	int m_scrollX;

	// 横座標
	int m_areaX;

	// 画面上マウス座標
	int m_mouseAreaX;

	// スクロールスピード
	int m_scrollSpeed;

	// 32ドットグリッド表示するかどうか
	bool m_is32DotGrid;

	// 64ドットグリッド表示するかどうか
	bool m_is64DotGrid;

	// 96ドットグリッド表示するかどうか
	bool m_is96DotGrid;


	/// --------------------------------------------------
	// 背景画像
	int m_backGroundDraw;


	/// --------------------------------------------------
	// キャラクター画像
	int m_charaDraw;


	/// --------------------------------------------------
	// 地面の画像
	int m_underGroundDraw;


	/// ---------------------------------------------------
	// エディタチップ画像
	int m_vChipDraw;

	// チップ配置座標
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

