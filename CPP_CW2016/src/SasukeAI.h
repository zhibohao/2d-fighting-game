#pragma once
#include "SasukeObject.h"
class SasukeAI :
	public SasukeObject
{
public:
	SasukeAI(FightEngine *pEngine, int playerId);
	~SasukeAI();

	void DoUpdate(int iCurrentTime);
	void InputControl(int stateInput);
	int AutoMove();
	bool CheckNarutoDirection();

};

