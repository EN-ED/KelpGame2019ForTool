#include "Project.hpp"
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include "DxLib.h"
#include "DragProject.hpp"


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


	SetWindowText("MapEditorForSoap");					// メインウインドウのウインドウタイトルを変更する
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
	SetDragFileValidFlag(TRUE);		// ドラッグアンドドロップ追加するように調整


	Project project = Project();
	SetKeyInputCursorBrinkFlag(TRUE);


	MouseData::UpDate();

	DragProject* pproject = nullptr;

	bool flag = false;

	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd())
	{
		MouseData::UpDate();
		KeyData::UpDate();

		// ドラッグアンドドロップが行われたとき
		if (GetDragFileNum() > 0)
		{
			char filePath[MAX_PATH];				// ファイルのパスを所持する仮置き変数

			GetDragFilePath(filePath);				// ドラッグアンドドロップのパスを取得

			pproject = new DragProject(filePath);
			flag = true;
		}

		if (flag)
		{
			pproject->Draw();
			pproject->Process();
		}
		else
		{
			project.Draw();
			project.Process();
		}
	}


	// 後片付け
	if (flag)
	{
		delete pproject;
	}
	InitGraph();
	DxLib_End();


	// プロジェクト終了
	return 0;
}