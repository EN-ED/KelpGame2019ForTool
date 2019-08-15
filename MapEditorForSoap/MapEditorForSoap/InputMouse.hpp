#pragma once
#ifndef _INPUTMOUSE_HPP
#define _INPUTMOUSE_HPP



// マウス
class MouseData
{
private:
	static int m_mouse[3];
	static int m_mouseInput;
	struct MouseXY
	{
		int x;
		int y;
	};
	static MouseXY m_preMouseArea;
	static MouseXY m_mouseArea;


public:
	//左クリックか右クリックか
	enum class ECLICK { LEFT, RIGHT, CENTER };


	//マウスのクリックの状態を更新する
	static void UpDate();

	//マウスのクリックの状態を返す
	static const int& GetClick(const ECLICK& t_mouseCode);

	// 現在のマウスの位置
	static const MouseXY& GetMouseArea();

	// 直前からどれくらい移動したか
	static const MouseXY GetMouseMoveValue();
};



// マウスホイール
class MouseWheelData
{
private:
	static int m_mouseWheel;
	static int m_oldMouseWheel;


public:
	//マウスのホイールの状態を更新
	static void UpDate();

	//マウスホイールの状態を返す
	static const int& GetMouseWheel();
};


#endif // !_INPUTMOUSE_HPP