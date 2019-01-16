#pragma once
#include "CharacterObject.h"
class SasukeObject :
	public CharacterObject
{
public:
	SasukeObject(FightEngine *pEngine, int playerId);
	~SasukeObject();

	void Draw();
	void DoUpdate(int iCurrentTime);

	virtual void SetState();
	void AttackJudgment();
	void MoveControl();
	void CheckFrame();

};

