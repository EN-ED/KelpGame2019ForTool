#pragma once
#ifndef _INPUTKEY_HPP
#define _INPUTKEY_HPP



// キーボードの入力状態
class KeyData
{
private:
	static int m_key[256];		// キーの入力状態格納用変数
	static char m_tmpKey[256];	// 現在のキーの入力状態を格納する

public:
	static void UpDate();			// キー入力の状態更新


	static const int& Get(const int& t_keyCode);		// キー入力状態取得
	static const bool IsCheckEnd();					// 強制終了
};


#endif // !_INPUTKEY_HPP