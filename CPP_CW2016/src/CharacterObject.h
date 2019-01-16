#pragma once

#include "DisplayableObject.h"
#include "PlayerState.h"
#include "JPGImage.h"
#include "FightEngine.h"

class CharacterObject :
	public DisplayableObject
{
public:
	CharacterObject(FightEngine* pEngine);
	~CharacterObject();

	PlayerState* GetCurrentState(int currentState);
	void BeAttacked(int state, int damage, int time, int dX, int dY);

	int GetDefenseCentreX();
	int GetDefenseCentreY() { return m_dY + m_defenseY + m_defenseH / 2; };
	int GetDefenseW() { return m_defenseW; };
	int GetDefenseH() { return m_defenseH; };
	int GetHp() { return m_hp; };
	int GetState() { return m_currentStateId; };
	int GetType() { return m_characterType; };
	bool GetAir() { return m_air; };
	int GetDirection() { return m_directionR; };

	void InputControl();
	bool IfRectangleIntersect(int centreX1, int centreY1, int w1, int h1, int X2, int Y2, int w2, int h2);
	void CheckDirection();
	void CheckPosition();
	bool CheckAttack();

	void CrackTile();
	void CelebratePose();
	void ChangeState(int state);
	
	virtual void SetState() = 0;

protected:
	FightEngine* m_pEngine;

	int m_dX;
	int m_dY;
	int m_dSY;
	
	int m_defenseX;
	int m_defenseY;
	int m_defenseW;
	int m_defenseH;

	int m_attackX;
	int m_attackY;
	int m_attackW;
	int m_attackH;

	int m_playerId;
	int m_direction;
	int m_characterType;
	int m_directionR;

	int m_currentStateId;
	int m_currentFrame;
	int m_counter;
	int m_drawStateId;

	int m_hp;
	int m_hurtDistanceX;
	int m_hurtDistanceY;
	int m_attackEnergy;

	bool m_air;
	bool m_landing;
	bool m_defense;

	PlayerState* m_currentState;
	PlayerState* Stand;
	PlayerState* Left;
	PlayerState* Right;
	PlayerState* Defense;
	PlayerState* BreakDefense;
	PlayerState* Attack;
	PlayerState* SecondAttack;
	PlayerState* ThirdAttack;
	PlayerState* Teleport;
	PlayerState* UpAttack;
	PlayerState* Jump;
	PlayerState* AirAttack;
	PlayerState* Hurt;
	PlayerState* KnockedDownGetUp;
	PlayerState* Celebrate;
	PlayerState* GetReady;
	PlayerState* ThoundsPain;

	ImageData m_image;

};

