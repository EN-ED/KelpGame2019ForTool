#include "MainProject.hpp"
#include "DxLib.h"
#include "InputKey.hpp"
#include "InputMouse.hpp"



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("GameDrawSizeEditor");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(255, 255, 255);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth, winHeight);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetAlwaysRunFlag(TRUE);			// 裏でもアクティブにする
	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(TRUE);			// マウスカーソルを表示する


	MainProject mainProject = MainProject();



	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd())
	{
		MouseData::UpDate();
		MouseWheelData::UpDate();
		KeyData::UpDate();

		mainProject.Draw();
		mainProject.Process();
	}


	// 後片付け
	mainProject.~MainProject();
	InitGraph();
	DxLib_End();


	// プロジェクト終了
	return 0;
}