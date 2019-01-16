#pragma once
#include "CharacterObject.h"
class NarutoObject :
	public CharacterObject
{
public:
	NarutoObject(FightEngine *pEngine, int playerId);
	~NarutoObject();

	void Draw();
	void DoUpdate(int iCurrentTime);

	virtual void SetState();
	void AttackJudgment();
	void MoveControl();
	void CheckFrame();

};

