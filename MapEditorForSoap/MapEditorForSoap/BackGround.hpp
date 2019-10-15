#pragma once
#include "DxLib.h"
#include "InputKey.hpp"


class BackGround
{
private:
	int mD_backGround;			// ”wŒi‰æ‘œ
	int mD_underGround;			// °‰æ‘œ

	int m_areaX;
	int m_speed;

	int m_allAreaX;


public:
	BackGround();
	~BackGround();


	void Draw();

	void Process();

	void SetSpeed(const float& t_speed);

	int GetAllAreaX() { return m_allAreaX; }

	void SetMoveX(int t_x, bool right)
	{
		if (right)
		{
			m_areaX += t_x;
			m_allAreaX += t_x;
			if (m_areaX > 1920) m_areaX = 0;
		}
		else
		{
			m_areaX -= t_x;
			m_allAreaX -= t_x;
			if (m_areaX > 1920) m_areaX = 0;
		}
	}

	int GetArea() { return m_areaX; }

	void SetReset()
	{
		m_areaX = 0;

		m_speed = 0;

		m_allAreaX = 0;
	}
};

