#pragma once
#include "CharacterObject.h"
class BirdObject :
	public CharacterObject
{
public:
	BirdObject(FightEngine *pEngine);
	~BirdObject();

	void Draw();
	void DoUpdate(int iCurrentTime);

	virtual void SetState();
	void MoveControl();
	void CheckFrame();
	void CheckPosition();
};

