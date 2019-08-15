#pragma once
#include "DxLib.h"



// キーボードの入力状態
class KeyData
{
private:
	static int key[256];		// キーの入力状態格納用変数
	static char tmpKey[256];	// 現在のキーの入力状態を格納する

public:
	static void UpDate();			// キー入力の状態更新
	static int Get(int t_keyCode);	// キー入力状態取得
	static bool CheckEnd();			// 強制終了
};