#pragma once
#include "BaseEngine.h"
#include "FightTileManager.h"

class NarutoObject;
class SasukeObject;
class HealthBarObject;
class NameBarObject;
class BackgroundControl;
class KakashiObject;
class SasukeAI;
class BirdObject;

class FightEngine :
	public BaseEngine
{
public:
	FightEngine();
	~FightEngine();

	void SetupBackgroundBuffer();
	void DrawStrings();
	void DrawStringsOnTop();
	void KeyDown(int keyCode);
	void MouseDown(int iButton, int iX, int iY);
	int InitialiseObjects();
	void GameAction();
	void InitTile();
	void DrawButton();
	void LoadRecord();
	void SaveRecord(int player1, int player2, int winner);

	FightTileManager& GetTileManager() { return m_tileManager; };
	
	/*
	Menu		0
	Select		1
	Battle		2
	Paused		3
	Transition	4
	Teach		5
	*/
	int GetState(){ return m_state; };
	void SetState(int state);

	enum State { stateMenu, stateSelect, stateBattle, statePaused, stateTransition, stateTeach, stateOver, stateRecord};

private:
	State m_state;
	int m_choice;
	int m_player1Choice;
	int m_player2Choice;
	int m_timeAct;
	int m_counter;
	int m_startTime;
	int m_winnerId;
	int m_iPauseStarted;
	int m_gameTime;

	bool m_gameFinish;
	bool m_player1;
	bool m_player2;

	FightTileManager m_tileManager;

	NarutoObject* m_player1Naruto;
	SasukeObject* m_player1Sasuke;

	NarutoObject* m_player2Naruto;
	SasukeObject* m_player2Sasuke;

	HealthBarObject* m_player1HealthBar;
	HealthBarObject* m_player2HealthBar;

	NameBarObject* m_player1NameBar;
	NameBarObject* m_player2NameBar;

	BackgroundControl* m_backgrondControl;

	KakashiObject* m_Kakashi;
	BirdObject* m_Bird;

	SasukeAI* m_SasukeAI;
};

