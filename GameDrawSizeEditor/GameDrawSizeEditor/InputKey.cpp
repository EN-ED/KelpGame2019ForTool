#include "InputKey.hpp"



//////////////////////////////////////////////キーボード////////////////////////////////////////////////////

int KeyData::key[256];
char KeyData::tmpKey[256];


/// ------------------------------------------------------------------------------------------------------------
void KeyData::UpDate()
{
	GetHitKeyStateAll(KeyData::tmpKey);	// 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		// i番のキーコードに対応するキーが押されていたら
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;
		}
		// キーが離された瞬間
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1;
		}
		// アクションがない
		else
		{
			KeyData::key[i] = 0;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
bool KeyData::CheckEnd()
{
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}



/// ------------------------------------------------------------------------------------------------------------
int KeyData::Get(int t_keyCode)
{
	return KeyData::key[t_keyCode];
}