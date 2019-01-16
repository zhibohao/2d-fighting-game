#include "header.h"
#include "templates.h"
#include "FightEngine.h"

#include "JPGImage.h"
#include "NarutoObject.h"
#include "SasukeObject.h"
#include "HealthBarObject.h"
#include "NameBarObject.h"
#include "BackgroundControl.h"
#include "KakashiObject.h"
#include "SasukeAI.h"
#include "BirdObject.h"

#include <fstream>
using namespace std;

FightEngine::FightEngine()
	: BaseEngine(10), m_state(stateMenu), m_choice(0), m_timeAct(20), m_counter(-1)
{
}

FightEngine::~FightEngine()
{
}

void FightEngine::InitTile() {
	m_tileManager.DrawAllTiles(this, GetBackground(), 0, 0, m_tileManager.GetCol() - 1, m_tileManager.GetRow() - 1);
}

void FightEngine::DrawButton() {
	ImageData button;
	button.LoadImage("../Image/KeyButton.png");
	switch (m_state) {
	case stateSelect:
		button.RenderImageWithMask(GetBackground(), 0, 0, 400, 500, 52, 57);
		button.RenderImageWithMask(GetBackground(), 52, 0, 348, 557, 156, 57);

		button.RenderImageWithMask(GetBackground(), 0, 57, 348, 650, 156, 57);

		button.RenderImageWithMask(GetBackground(), 0, 114, 828, 500, 52, 57);
		button.RenderImageWithMask(GetBackground(), 52, 114, 776, 557, 156, 57);

		button.RenderImageWithMask(GetBackground(), 0, 171, 776, 650, 156, 57);
		break;
	}
}

void FightEngine::LoadRecord() {
	ifstream file;
	file.open("../record.txt");
	char buffer[32];
	int line = 0;
	while (file.getline(buffer, 32)) {
		if (line > 7) {
			break;
		}

		char player[32];
		switch (buffer[0]) {
		case '0':
			sprintf(player, "Naruto");
			break;
		case '1':
			sprintf(player, "Sasuke");
			break;
		}
		DrawBackgroundString(197, 23 + line * 100, player, 0xffffff, GetFont("Cornerstone Regular.ttf", 50));
		DrawBackgroundString(200, 20 + line * 100, player, 0XF44336, GetFont("Cornerstone Regular.ttf", 50));
		DrawBackgroundString(600, 23 + line * 100, "VS", 0xffffff, GetFont("Cornerstone Regular.ttf", 50));
		DrawBackgroundString(600, 20 + line * 100, "VS", 0, GetFont("Cornerstone Regular.ttf", 50));
		switch (buffer[1]) {
		case '0':
			sprintf(player, "Naruto");
			break;
		case '1':
			sprintf(player, "Sasuke");
			break;
		}
		DrawBackgroundString(878, 23 + line * 100, player, 0xffffff, GetFont("Cornerstone Regular.ttf", 50));
		DrawBackgroundString(875, 20 + line * 100, player, 0X2196F3, GetFont("Cornerstone Regular.ttf", 50));
		switch (buffer[2]) {
		case '0':
			DrawBackgroundString(447, 33 + line * 100, "Win", 0xffffff, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(450, 30 + line * 100, "Win", 0xFFEA00, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(743, 33 + line * 100, "Lose", 0xffffff, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(740, 30 + line * 100, "Lose", 0x424242, GetFont("Cornerstone Regular.ttf", 40));
			break;
		case '1':
			DrawBackgroundString(447, 33 + line * 100, "Lose", 0xffffff, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(450, 30 + line * 100, "Lose", 0x424242, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(743, 33 + line * 100, "Win", 0xffffff, GetFont("Cornerstone Regular.ttf", 40));
			DrawBackgroundString(740, 30 + line * 100, "Win", 0xFFEA00, GetFont("Cornerstone Regular.ttf", 40));
			break;
		}
		line++;
	}
	file.close();

	if (line == 0) {
		DrawBackgroundString(510, 200, "No Record", 0x424242, GetFont("Cornerstone Regular.ttf", 50));
	}
}

void FightEngine::SaveRecord(int player1, int player2, int winner) {
	ifstream inputFile;
	ofstream outputFile;
	char buffer[32];
	inputFile.open("../record.txt");
	outputFile.open("../recordTemp.txt");
	while (inputFile.getline(buffer, 32)) {
		outputFile << buffer << endl;
	}
	inputFile.close();
	outputFile.close();

	sprintf(buffer, "%d%d%d", player1, player2, winner);
	outputFile.open("../record.txt");
	outputFile << buffer << endl;
	outputFile.close();

	outputFile.open("../record.txt", ios::app);
	inputFile.open("../recordTemp.txt");
	while (inputFile.getline(buffer, 32)) {
		outputFile << buffer << endl;
	}
	inputFile.close();
	outputFile.close();
}

void FightEngine::SetupBackgroundBuffer() {
	Redraw(true);
	ImageData background, choice, avatar, character, determine, hp, vs, tree;
	switch (m_state) {
	case stateMenu:
		background.LoadImage("../Image/MenuBackground.png");
		background.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, background.GetWidth(), background.GetHeight());
		
		choice.LoadImage("../Image/MenuChoice.png");
		choice.RenderImageWithMask(this->GetBackground(),
			0, 0, 470, 300 + m_choice * 100, choice.GetWidth(), choice.GetHeight());

		break;

	case stateSelect:
		background.LoadImage("../Image/SelectBackground.png");
		background.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, background.GetWidth(), background.GetHeight());

		vs.LoadImage("../Image/vs.png");
		vs.RenderImageWithMask(this->GetBackground(),
			0, 0, 540, 5, vs.GetWidth(), vs.GetHeight());

		avatar.LoadImage("../Image/SelectAvatar.png");
		avatar.RenderImageWithMask(this->GetBackground(),
			0, 0, 20, 20, avatar.GetWidth(), avatar.GetHeight());

		choice.LoadImage("../Image/SelectChoice.png");
		choice.RenderImageWithMask(this->GetBackground(),
			0, 0, 14 + m_player1Choice * 125, 14, choice.GetWidth(), choice.GetHeight());

		character.LoadImage("../Image/SelectCharacter.png");
		character.RenderImageWithMask(this->GetBackground(),
			m_player1Choice * 185, 0, 80, 200, 185 + m_player1Choice * 39, character.GetHeight());

		avatar.RenderImageWithMask(this->GetBackground(),
			0, 0, 1016, 20, avatar.GetWidth(), avatar.GetHeight());

		choice.RenderImageWithMask(this->GetBackground(),
			0, 0, 1010 + m_player2Choice * 125, 14, choice.GetWidth(), choice.GetHeight());

		character.RenderImageWithMask(this->GetBackground(),
			m_player2Choice * 185, 0, 990, 200, 185 + m_player2Choice * 39, character.GetHeight());	

		DrawButton();

		if (m_player1) {
			determine.LoadImage("../Image/SelectDetermine.png");
			determine.RenderImageWithMask(this->GetBackground(),
				m_player1Choice * 100, 0, 400, 110, 100, determine.GetHeight());
		}

		if (m_player2) {
			determine.LoadImage("../Image/SelectDetermine.png");
			determine.RenderImageWithMask(this->GetBackground(),
				m_player2Choice * 100, 0, 790, 110, 100, determine.GetHeight());
		}
		
		break;

	case stateBattle:
		background.LoadImage("../Image/BattleBackground.png");
		background.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, 1280, 800);

		avatar.LoadImage("../Image/SelectAvatar.png");
		avatar.RenderImageWithMask(this->GetBackground(),
			m_player1Choice * 123, 0, 10, 10, 119, avatar.GetHeight());
		avatar.RenderImageWithMask(this->GetBackground(),
			m_player2Choice * 123, 0, 1151, 10, 119, avatar.GetHeight());

		hp.LoadImage("../Image/BattleHp.png");
		hp.RenderImageWithMask(this->GetBackground(),
			0, 0, 147, 83, hp.GetWidth() / 2 - 1, hp.GetHeight());
		hp.RenderImageWithMask(this->GetBackground(),
			hp.GetWidth() / 2 - 1, 0, 709, 83, hp.GetWidth() / 2, hp.GetHeight());

		InitTile();

		break;

	case stateTeach:
		background.LoadImage("../Image/TeachBackground1.png");
		background.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, 1280, 800);

		tree.LoadImage("../Image/TeachBackground2.png");
		tree.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, 1280, 800);

		InitTile();
		break;
	case stateRecord:
		background.LoadImage("../Image/SelectBackground.png");
		background.RenderImageWithMask(this->GetBackground(),
			0, 0, 0, 0, 1280, 800);

		LoadRecord();
		break;
	}
}

int FightEngine::InitialiseObjects()
{
	DrawableObjectsChanged();
	DestroyOldObjects();
	
	switch (m_state) {
	case stateMenu:
	case stateRecord:
	case stateSelect:

		// New Feature!
		m_backgrondControl = new BackgroundControl(this);
		AddObject(m_backgrondControl);

		break;
	case stateBattle:
		CreateObjectArray(10);
		if (m_choice == 0) {
			m_player1Choice = 0;
			m_player2Choice = 1;
			m_player1Naruto = new NarutoObject(this, 1);
			m_SasukeAI = new SasukeAI(this, 2);

			m_player1HealthBar = new HealthBarObject(this, 1);
			m_player2HealthBar = new HealthBarObject(this, 2);
			m_backgrondControl = new BackgroundControl(this);

			StoreObjectInArray(0, m_player1Naruto);
			StoreObjectInArray(1, m_SasukeAI);
			StoreObjectInArray(2, m_player1HealthBar);
			StoreObjectInArray(3, m_player2HealthBar);
			StoreObjectInArray(4, m_backgrondControl);

			return 0;
		}

		switch (m_player1Choice) {
		case 0:
			m_player1Naruto = new NarutoObject(this, 1);
			StoreObjectInArray(0, m_player1Naruto);
			break;
		case 1:
			m_player1Sasuke = new SasukeObject(this, 1);
			StoreObjectInArray(0, m_player1Sasuke);
			break;
		}

		switch (m_player2Choice) {
		case 0:
			m_player2Naruto = new NarutoObject(this, 2);
			StoreObjectInArray(1, m_player2Naruto);
			break;
		case 1:
			m_player2Sasuke = new SasukeObject(this, 2);
			StoreObjectInArray(1, m_player2Sasuke);
			break;
		}
		m_player1NameBar = new NameBarObject(this, 1);
		m_player2NameBar = new NameBarObject(this, 2);
		m_player1HealthBar = new HealthBarObject(this, 1);
		m_player2HealthBar = new HealthBarObject(this, 2);
		m_backgrondControl = new BackgroundControl(this);

		StoreObjectInArray(2, m_player1HealthBar);
		StoreObjectInArray(3, m_player2HealthBar);
		StoreObjectInArray(4, m_player1NameBar);
		StoreObjectInArray(5, m_player2NameBar);
		StoreObjectInArray(6, m_backgrondControl);

		break;

	case stateTeach:
		CreateObjectArray(5);
		m_player1Naruto = new NarutoObject(this, 1);
		m_Kakashi = new KakashiObject(this, 2);
		m_Bird = new BirdObject(this);

		m_backgrondControl = new BackgroundControl(this);
		StoreObjectInArray(0, m_player1Naruto);
		StoreObjectInArray(1, m_Kakashi);
		StoreObjectInArray(2, m_Bird);
		StoreObjectInArray(3, m_backgrondControl);
		break;
	}

	return 0;
}

void FightEngine::GameAction() {
	if (!IsTimeToAct()) {
		return;
	}
	SetTimeToAct(m_timeAct);

	switch (m_state) {
	case statePaused:
		DrawStringsOnTop();
		return;
	case stateTransition:
		if(m_backgrondControl->IsFinish()){
			switch (m_backgrondControl->GetScene()) {
			case 0:
			case 3:
				m_state = stateSelect;
				m_player1Choice = 0;
				m_player2Choice = 1;
				m_player1 = false;
				m_player2 = false;
				InitialiseObjects();

				SetupBackgroundBuffer();
				break;
			case 1:
				m_state = stateMenu;
				m_choice = 0;
				InitialiseObjects();

				SetupBackgroundBuffer();
				break;
			case 2:
				m_state = stateBattle;
				InitialiseObjects();
				m_startTime = GetModifiedTime() / 1000;
				m_counter = -1;
				m_gameFinish = false;

				SetupBackgroundBuffer();
				break;
			case 4:
				m_state = stateTeach;
				InitialiseObjects();

				SetupBackgroundBuffer();
				break;
			case 5:
				m_state = stateRecord;
				InitialiseObjects();

				SetupBackgroundBuffer();
				break;
			}
		}

		UpdateAllObjects(GetModifiedTime());
		break;
	case stateSelect:
		if (m_player1 && m_player2) {
			m_state = stateTransition;
			m_backgrondControl->BackgroundTransition(2);
		}

		break;
	case stateBattle:
		if ((m_player1HealthBar->GetHp() <= 0) || (m_player2HealthBar->GetHp() <= 0)) {
			m_gameFinish = true;
			m_winnerId = (m_player1HealthBar->GetHp() <= 0) ? 1 : 0;
		}
		
		if (m_gameFinish) {
			if (m_counter > 0) {
				m_timeAct = 80;
				m_counter--;

				if (m_winnerId != -1) {
					CharacterObject* winner = dynamic_cast<CharacterObject*> (this->GetDisplayableObject(m_winnerId));
					winner->CelebratePose();
				}
			}
			if (m_counter == -1) {
				m_counter = 60;
			}
			if (m_counter == 0){
				m_counter--;
				m_timeAct = 20;
				SaveRecord(m_player1Choice, m_player2Choice, m_winnerId);
				if (m_choice != 0) {
					m_state = stateTransition;
					m_backgrondControl->BackgroundTransition(3);
				}
				else {
					Redraw(true);
					m_state = stateOver;
				}
			}
		}

		m_tileManager.RepairTile();

		UpdateAllObjects(GetModifiedTime());
		break;
	case stateTeach:
		if ((m_player1Naruto->GetState() == 2) && (m_player1Naruto->GetXCentre() == 1238)) {
			m_backgrondControl->MoveBackground(1);
			Redraw(true);
		}
		if ((m_player1Naruto->GetState() == 1) && (m_player1Naruto->GetXCentre() == 42)) {
			m_backgrondControl->MoveBackground(0);
			Redraw(true);
		}

		m_tileManager.RepairTile();
		UpdateAllObjects(GetModifiedTime());
		break;
	case stateOver:
		m_tileManager.RepairTile();
		UpdateAllObjects(GetModifiedTime());
		break;
	case stateRecord:
		UpdateAllObjects(GetModifiedTime());
		break;
	}
}


void FightEngine::DrawStrings() {
	switch (m_state) {
	case stateMenu:
		DrawScreenString(553, 303, "Normal", 0XFF9800, GetFont("Cornerstone Regular.ttf", 50));
		DrawScreenString(550, 300, "Normal", 0XFF5722, GetFont("Cornerstone Regular.ttf", 50));
		
		DrawScreenString(553, 403, "VS Human", 0XFF9800, GetFont("Cornerstone Regular.ttf", 50));
		DrawScreenString(550, 400, "VS Human", 0XFF5722, GetFont("Cornerstone Regular.ttf", 50));

		DrawScreenString(553, 503, "Record", 0XFF9800, GetFont("Cornerstone Regular.ttf", 50));
		DrawScreenString(550, 500, "Record", 0XFF5722, GetFont("Cornerstone Regular.ttf", 50));

		DrawScreenString(553, 603, "Exit", 0XFF9800, GetFont("Cornerstone Regular.ttf", 50));
		DrawScreenString(550, 600, "Exit", 0XFF5722, GetFont("Cornerstone Regular.ttf", 50));
		break;
	case stateSelect:
		DrawScreenString(303, 53, "Player 1", 0XFFFFFF, GetFont("Cornerstone Regular.ttf", 40));
		DrawScreenString(300, 50, "Player 1", 0XF44336, GetFont("Cornerstone Regular.ttf", 40));

		DrawScreenString(783, 53, "Player 2", 0XFFFFFF, GetFont("Cornerstone Regular.ttf", 40));
		DrawScreenString(780, 50, "Player 2", 0X2196F3, GetFont("Cornerstone Regular.ttf", 40));
		break;
	case stateBattle:
		CopyBackgroundPixels(595, 50, 100, 100);
		char buffer[32];
		if (m_counter == -1) {
			m_gameTime = 61 - GetModifiedTime() / 1000 + m_startTime;
			if (m_gameTime <= 0) {
				m_gameFinish = true;
				m_winnerId = -1;
			}
		}
		sprintf(buffer, "%d", m_gameTime);
		DrawScreenString(600, 50, buffer, 0xE65100, GetFont("Cornerstone Regular.ttf", 60));

		break;
	}
}

void FightEngine::DrawStringsOnTop() {
	switch (m_state) {
	case statePaused:
		Redraw(true);
		char buffer[32];
		sprintf(buffer, "%d", m_gameTime);
		DrawScreenString(600, 50, buffer, 0xE65100, GetFont("Cornerstone Regular.ttf", 60));
		DrawScreenString(500, 350, "Paused", 0x424242, GetFont("Cornerstone Regular.ttf", 80));
		break;
	case stateBattle:
		if ((m_counter > 0) && (m_winnerId != -1)) {
			DrawScreenString(205, 205, "Winner", 0xFF9100, GetFont("Cornerstone Regular.ttf", 100));
			DrawScreenString(200, 200, "Winner", 0xFFEA00, GetFont("Cornerstone Regular.ttf", 100));

			int winnerId = (m_player1HealthBar->GetHp() <= 0) ? 2 : 1;
			int color = (winnerId == 1) ? 0XF44336 : 0X2196F3;
			char buffer[32];
			if (m_choice == 0) {
				if (m_winnerId == 0) {
					sprintf(buffer, "Naruto");
				}
				else {
					sprintf(buffer, "Sasuke");
				}
			}
			else {
				sprintf(buffer, "Player %d", winnerId);
			}
			DrawScreenString(403, 363, buffer, 0XFFFFFF, GetFont("Cornerstone Regular.ttf", 70));
			DrawScreenString(400, 360, buffer, color, GetFont("Cornerstone Regular.ttf", 70));

			if ((m_player1HealthBar->GetHp() == 100) || (m_player2HealthBar->GetHp() == 100)) {
				DrawScreenString(303, 308, "Perfect", 0xFF9100, GetFont("Cornerstone Regular.ttf", 50));
				DrawScreenString(300, 305, "Perfect", 0xFFEA00, GetFont("Cornerstone Regular.ttf", 50));
			}
		}
		break;
	case stateOver:
		DrawScreenString(345, 205, "Try Again?", 0x424242, GetFont("Cornerstone Regular.ttf", 100));
		DrawScreenString(340, 200, "Try Again?", 0xFFFFFF, GetFont("Cornerstone Regular.ttf", 100));

		DrawScreenString(363, 353, "Yes        NO", 0x424242, GetFont("Cornerstone Regular.ttf", 70));
		DrawScreenString(360, 350, "Yes        NO", 0xFFFFFF, GetFont("Cornerstone Regular.ttf", 70));

		DrawScreenString(363, 433, " Y          N", 0x424242, GetFont("Cornerstone Regular.ttf", 70));
		DrawScreenString(360, 430, " Y          N", 0xFFFFFF, GetFont("Cornerstone Regular.ttf", 70));
		break;
	}
}

void FightEngine::KeyDown(int keyCode) {
	switch (m_state)
	{
	case stateMenu:
		switch (keyCode) {
		case 119:
		case 1073741906:
			m_choice = (m_choice + 3) % 4;
			SetupBackgroundBuffer();
			break;
		case 115:
		case 1073741905:
			m_choice = (m_choice + 1) % 4;
			SetupBackgroundBuffer();
			break;
		case 32:
		case 13:
			switch (m_choice) {
			case 0:
				m_state = stateTransition;
				m_backgrondControl->BackgroundTransition(4);
				break;
			case 1:
				m_state = stateTransition;
				m_backgrondControl->BackgroundTransition(0);
				break;
			case 2:
				m_state = stateTransition;
				m_backgrondControl->BackgroundTransition(5);
				break;
			case 3:
				SetExitWithCode(0);
				break;
			}
			break;
		}
		break;
	case stateSelect:
		switch (keyCode) {
		case 97:
		case 100:
			if (!m_player1) {
				m_player1Choice = (m_player1Choice + 1) % 2;
				SetupBackgroundBuffer();
			}
			break;
		case 1073741903:
		case 1073741904:
			if (!m_player2) {
				m_player2Choice = (m_player2Choice + 1) % 2;
				SetupBackgroundBuffer();
			}
			break;
		case 106:
			if (!m_player1) {
				m_player1 = true;
				SetupBackgroundBuffer();
			}
			break;
		case 1073741913:
			if (!m_player2) {
				m_player2 = true;
				SetupBackgroundBuffer();
			}
			break;
		case 107:
		case 1073741914:
			m_state = stateTransition;
			m_backgrondControl->BackgroundTransition(1);
			break;
		}
		break;
	case stateBattle:
		switch (keyCode) {
		case 32:
			m_state = statePaused;
			m_iPauseStarted = GetTime();
			break;
		}
		break;
	case statePaused:
		switch (keyCode) {
		case 32:
			m_state = stateBattle;
			IncreaseTimeOffset(m_iPauseStarted - GetTime());
			break;
		}
		break;
	case stateOver:
		switch (keyCode) {
		case 121:
			m_state = stateTransition;
			m_backgrondControl->BackgroundTransition(2);
			break;
		case 110:
			m_state = stateTransition;
			m_backgrondControl->BackgroundTransition(1);

			break;
		}
		break;
	case stateRecord:
		switch (keyCode) {
		case 107:
			m_state = stateTransition;
			m_backgrondControl->BackgroundTransition(1);

			break;
		}

		break;
	}
}

void FightEngine::MouseDown(int iButton, int iX, int iY) {
	switch (m_state) {
	case stateTeach:
	case stateBattle:
		CharacterObject* currentCharacter;
		currentCharacter = dynamic_cast<CharacterObject*> (this->GetDisplayableObject(0));
		currentCharacter->CelebratePose();

		break;
	}
}

/*
Menu		0
Select		1
Battle		2
Paused		3
Transition	4
Teach		5
*/
void FightEngine::SetState(int state) {
	switch (state) {
	case 0:
		m_state = stateMenu;
		break;
	case 1:
		m_state = stateSelect;
		break;
	case 2:
		m_state = stateBattle;
		break;
	case 3:
		m_state = statePaused;
		break;
	case 4:
		m_state = stateTransition;
		break;
	case 5:
		m_state = stateTeach;
		break;
	}
}