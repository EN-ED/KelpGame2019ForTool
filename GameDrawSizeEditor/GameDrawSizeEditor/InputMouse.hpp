#pragma once
#include "DxLib.h"

// マウスの左か右か
enum class CLICK { LEFT, RIGHT };


class MouseData
{
private:
	static int m_Mouse[3];
	static int MouseInput;

public:
	MouseData();
	~MouseData();

	//マウスのクリックの状態を更新する
	static void Mouse_UpDate();

	//マウスのクリックの状態を返す
	static int GetClick(int MouseCode);
};


class MouseWheelData
{
private:
	static int m_MouseWheel;
	static int old_MouseWheel;

public:
	MouseWheelData();
	~MouseWheelData();

	//マウスのホイールの状態を更新
	static void MouseWheel_Update();

	//マウスホイールの状態を返す
	static int GetMouseWheel(int MouseWheelCode);
};