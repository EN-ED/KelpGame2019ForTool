#include "Garbage.hpp"



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Garbage::Garbage(const int t_x, const int t_y, EDrawID t_ID)
{
	m_x = t_x;
	m_y = t_y;

	mD_garbage = -1;
	m_ID = t_ID;
	switch (t_ID)
	{
	case EDrawID::doro:
		mD_garbage = LoadGraph("media\\item\\Doro.png");
		break;

	case EDrawID::mizutamari:
		mD_garbage = LoadGraph("media\\item\\mizutamari.png");
		break;

	case EDrawID::sekiyu:
		mD_garbage = LoadGraph("media\\item\\Sekiyu.png");
		break;

	default:
		break;
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
Garbage::~Garbage()
{
	if (mD_garbage != -1) DeleteGraph(mD_garbage);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Garbage::Draw()
{
	DrawGraph(m_x, m_y, mD_garbage, true);
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void Garbage::Process(const int& t_speed)
{
	m_x -= t_speed;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& Garbage::GetX() const
{
	return m_x;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int& Garbage::GetY() const
{
	return m_y;
}



const Garbage::EDrawID& Garbage::GetID() const
{
	return m_ID;
}
