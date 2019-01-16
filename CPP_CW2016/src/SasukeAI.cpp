#include "header.h"
#include "SasukeAI.h"


SasukeAI::SasukeAI(FightEngine *pEngine, int playerId)
	:SasukeObject(pEngine, playerId)
{
	m_playerId = playerId;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = 100 * 2;
	m_iDrawHeight = 100 * 2;

	m_dX = m_playerId == 1 ? 200 : 900;
	m_dY = 540;
	m_air = false;

	m_iPreviousScreenX = m_iCurrentScreenX = m_dX;
	m_iPreviousScreenY = m_iCurrentScreenY = m_dY;

	m_direction = m_playerId - 1;
	m_characterType = 1;

	m_defenseX = 27 * 2;
	m_defenseY = 40 * 2;
	m_defenseW = 50 * 2;
	m_defenseH = 50 * 2;

	m_image.LoadImage("../Image/Sasuke.png");

	SetState();
	CelebratePose();

	SetVisible(true);
}

SasukeAI::~SasukeAI()
{
}

void SasukeAI::InputControl(int stateInput) {

	int state = m_currentStateId;
	if (m_currentState->GetControl() && (!m_landing)) {
		switch (stateInput) {
		case 1:
			state = stateInput;
			m_direction = 1;
			break;
		case 2:
			state = stateInput;
			m_direction = 0;
			break;
		case 8:
			if ((!m_air) || (m_dSY < 0)) {
				state = stateInput;
			}
			break;
		default:
			state = stateInput;
			break;
		}
	}

	if ((m_currentFrame == m_currentState->GetWait()) && (stateInput == 5)) {
		state++;
	}

	if (state != m_currentStateId) {
		m_currentStateId = state;
		m_currentState = GetCurrentState(m_currentStateId);
		m_counter = 0;
		m_currentFrame = 0;
	}

	return;
}

bool SasukeAI::CheckNarutoDirection() {
	CharacterObject* Naruto = dynamic_cast<CharacterObject*> (m_pEngine->GetDisplayableObject(0));

	if ((Naruto->GetXCentre() <= GetXCentre()) && (Naruto->GetDirection() == 0)) {
		return true;
	}
	if ((Naruto->GetXCentre() > GetXCentre()) && (Naruto->GetDirection() == 1)) {
		return true;
	}
	return false;
}

int SasukeAI::AutoMove() {
	CharacterObject* Naruto = dynamic_cast<CharacterObject*> (m_pEngine->GetDisplayableObject(0));
	if (Naruto->GetHp() <= 0) {
		if (m_currentStateId != 0) {
			return 14;
		}
		else {
			return 0;
		}
	}

	if (m_currentFrame == m_currentState->GetWait()) {
		if (Naruto->GetState() == 12) {
			return 5;
		}
	}

	if ((!m_currentState->GetControl()) || (m_landing)) {
		return 0;
	}

	CheckDirection();
	
	int distance = SDL_abs(Naruto->GetXCentre() - GetXCentre());
	int NarutoState = Naruto->GetState();
	int temp;
	if (NarutoState == 13) {
		return 8;
	}
	if (!m_air) {
		if ((distance < 150)) {
			temp = rand() % 16;
			
			switch (temp) {
			case 0:
			case 1:
			case 2:
			case 3:
				return 5;
			case 4:
			case 5:
				return 9;
			}
		}
		if (distance < 380) {
			temp = rand() % 20;
			if (temp  == 0) {
				return 4;
			}
		}
		if (CheckNarutoDirection() && Naruto->CheckAttack() && (distance < 300)) {
			switch (NarutoState) {
			case 4:
			case 11:
				temp = rand() % 50;
				if (temp == 0) {
					return 8;
				}
			default:
				if (distance < 200) {
					return 3;
				}
				break;
			}
		}
	}
	else {
		if (distance < 340) {
			temp = rand() % 3;
			if (temp == 0) {
				return 11;
			}
		}
	}

	temp = rand() % 50;
	if (temp == 0) {
		return 10;
	}

	if (distance > 400) {
		temp = rand() % 20;
		if (temp == 0) {
			return 8;
		}
	}

	switch (m_direction) {
	case 0:
		return 2;
	case 1:
		return 1;
	}

	return 0;
}

void SasukeAI::DoUpdate(int iCurrentTime) {

		InputControl(AutoMove());

		CheckFrame();

		MoveControl();

		CheckDirection();

		if ((m_attackH > 0) && (m_attackW > 0) && (m_pEngine->GetState() == 2)){
			AttackJudgment();
		}

		CheckPosition();

		m_iCurrentScreenX = m_dX;
		m_iCurrentScreenY = m_dY;

		RedrawObjects();
	}