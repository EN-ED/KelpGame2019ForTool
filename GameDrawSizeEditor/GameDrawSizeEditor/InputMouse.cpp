#include "InputMouse.hpp"
#include "DxLib.h"



/// ------------------------------------------------------------------------------------------------------------

int MouseData::m_mouse[3];
int MouseData::m_mouseInput;
MouseData::MouseXY MouseData::m_preMouseArea;
MouseData::MouseXY MouseData::m_mouseArea;



/// ------------------------------------------------------------------------------------------------------------
void MouseData::UpDate()
{
	// PCゲーである以上、マウスのない状態が想定できないのでエラー処理は省く
	m_mouseInput = GetMouseInput();

	m_preMouseArea.x = m_mouseArea.x;
	m_preMouseArea.y = m_mouseArea.y;
	GetMousePoint(&m_mouseArea.x, &m_mouseArea.y);


	for (int i = 0; i != 3; ++i)
	{
		// 押されていなかったら
		if ((m_mouseInput & 1 << i)/* 左は1 / 右は2 / 真ん中は4 */ == 0)
		{
			if (m_mouse[i] < 0)
			{
				m_mouse[i] = 0;
			}
			else if (m_mouse[i] > 0)
			{
				m_mouse[i] = -1;
			}
		}
		// 押されていたら
		else
		{
			m_mouse[i]++;
		}
	}
}



/// ------------------------------------------------------------------------------------------------------------
const int& MouseData::GetClick(const ECLICK& t_mouseCode)
{
	return m_mouse[static_cast<int>(t_mouseCode)];
}



/// ------------------------------------------------------------------------------------------------------------
const MouseData::MouseXY& MouseData::GetMouseArea()
{
	return m_mouseArea;
}



/// ------------------------------------------------------------------------------------------------------------
const MouseData::MouseXY MouseData::GetMouseMoveValue()
{
	return { m_mouseArea.x - m_preMouseArea.x, m_mouseArea.y - m_preMouseArea.y };
}



/// ------------------------------------------------------------------------------------------------------------

int MouseWheelData::m_mouseWheel;
int MouseWheelData::m_oldMouseWheel;



/// ------------------------------------------------------------------------------------------------------------
void MouseWheelData::UpDate()
{
	if (m_oldMouseWheel == m_mouseWheel)
	{
		if (m_mouseWheel != 0) m_mouseWheel = 0;
		return;
	}
	else
	{
		m_oldMouseWheel = m_mouseWheel;
	}


	if (m_oldMouseWheel - m_mouseWheel > 0)
	{
		m_mouseWheel++;
	}
	else if (m_oldMouseWheel - m_mouseWheel < 0)
	{
		m_mouseWheel--;
	}
}



/// ------------------------------------------------------------------------------------------------------------
const int& MouseWheelData::GetMouseWheel()
{
	return m_mouseWheel += GetMouseWheelRotVol();
}