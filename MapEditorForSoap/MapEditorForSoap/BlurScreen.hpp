#pragma once
#ifndef _BLURSCREEN_HPP
#define _BLURSCREEN_HPP
#include "DxLib.h"


struct BlurScreen
{
private:
	int m_screen[2];
	int m_current;
	int m_alpha;
	int m_screenWidth, m_screenHeight;
	int m_offsetX1, m_offsetX2, m_offsetY1, offsetY2;
	int m_notBlendDraw;


public:
	BlurScreen()
	{
		m_screen[0] = 0;
		m_screen[1] = 0;
		m_current = 0;
		m_alpha = 0;
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_offsetX1 = 0;
		m_offsetX2 = 0;
		m_offsetY1 = 0;
		offsetY2 = 0;
		m_notBlendDraw = 0;
	}
	~BlurScreen() {}


	void Init(int alpha, int offsetX1, int offsetY1, int offsetX2, int offsetY2);
	void ReplayInit();
	void Release();

	void PreRenderBlurScreen();

	void PostRenderBlurScreen();
};

#endif // !_BLURSCREEN_HPP