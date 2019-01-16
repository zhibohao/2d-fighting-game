#include "PlayerState.h"

/*
0	Stand				None
1	Left				a
2	Right				d
3	Defense				s
4	Break defense		s + j => e
5	Attack				j
6	Second Attack		j -> j
7	Third Attack		j -> j -> j
8	Teleport			l
9	Up Attack			w + j => q
10	Jump				k
11	Air Attack			j (up in the air)
12	Hurt
13	Knocked down & Get up
14	Celebrate
*/
PlayerState::PlayerState(int state)
{
	m_wait = -1;
	for (int i = 0; i < 20; i++) {
		m_duration[i] = -1;
	}
	switch (state)
	{
	case 0:
		m_numberFrame = 4;
		m_control = true;
		break;
	case 1:
		m_numberFrame = 6;
		m_control = true;
		break;
	case 2:
		m_numberFrame = 6;
		m_control = true;
		break;
	case 3:
		m_numberFrame = 1;
		m_control = true;
		break;
	case 4:
		m_numberFrame = 5;
		m_control = false;
		break;
	case 5:
		m_numberFrame = 3;
		m_wait = 2;
		m_control = false;
		break;
	case 6:
		m_numberFrame = 3;
		m_wait = 2;
		m_control = false;
		break;
	case 7:
		m_numberFrame = 6;
		m_control = false;
		break;
	case 8:
		m_numberFrame = 3;
		m_control = false;
		break;
	case 9:
		m_numberFrame = 3;
		m_control = false;
		break;
	case 10:
		m_numberFrame = 3;
		m_control = true;
		break;
	case 11:
		m_numberFrame = 5;
		m_control = false;
		break;
	case 12:
		m_numberFrame = 1;
		m_control = false;
		break;
	case 13:
		m_numberFrame = 8;
		m_control = false;
		break;
	case 14:
		m_numberFrame = 3;
		m_control = false;
		break;
	}
}


PlayerState::~PlayerState()
{
}

void PlayerState::SetDuration(int duration[20]) {
	for (int i = 0; i < m_numberFrame; i++) {
		m_duration[i] = duration[i];
	}
}