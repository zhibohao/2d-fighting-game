#pragma once
#include "DisplayableObject.h"
class HealthBarObject :
	public DisplayableObject
{
public:
	HealthBarObject(BaseEngine *pEngine, int playerId);
	~HealthBarObject();

	void Draw();
	void DoUpdate(int iCurrentTime);
	
	int CheckColor(int hp);
	int GetHp() { return m_hp; };

private:
	int m_playerId;
	int m_hp;
};

