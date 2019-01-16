#pragma once
#include "CharacterObject.h"
class KakashiObject :
	public CharacterObject
{
public:
	KakashiObject(FightEngine *pEngine, int playerId);
	~KakashiObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	virtual void SetState();
	PlayerState* GetCurrentState(int currentState);
	void CheckFrame();
	void CheckDialog();
	void CheckState();
	void ChangeState(int state);
	void DrawBackground();
	void CheckNaturo();
	void MoveControl(); 

private:
	PlayerState* Stand;
	PlayerState* Read;
	PlayerState* PoseGO;
	PlayerState* SennenGoroshi;

	ImageData m_dialog, m_button;

	int m_state;
	int m_durationCounter;
	int m_duration[20];
	char m_word1[64];
	char m_word2[64];
	bool m_finished;
};

