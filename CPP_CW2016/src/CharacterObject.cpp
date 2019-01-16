#include "header.h"
#include "CharacterObject.h"


CharacterObject::CharacterObject(FightEngine* pEngine)
	: DisplayableObject(pEngine)
{
	m_pEngine = pEngine;

	m_dSY = 0;

	m_air = false;
	m_landing = false;
	m_defense = false;

	Stand = new PlayerState(0);
	Left = new PlayerState(1);
	Right = new PlayerState(2);
	Defense = new PlayerState(3);
	BreakDefense = new PlayerState(4);
	Attack = new PlayerState(5);
	SecondAttack = new PlayerState(6);
	ThirdAttack = new PlayerState(7);
	Teleport = new PlayerState(8);
	UpAttack = new PlayerState(9);
	Jump = new PlayerState(10);
	AirAttack = new PlayerState(11);
	Hurt = new PlayerState(12);
	KnockedDownGetUp = new PlayerState(13);
	Celebrate = new PlayerState(14);

	m_currentStateId = 0;
	m_currentState = GetCurrentState(0);
	m_currentFrame = 0;
	m_counter = 0;
	m_drawStateId = 0;

	m_attackX = 0;
	m_attackY = 0;
	m_attackW = 0;
	m_attackH = 0;

	m_attackEnergy = 0;
	m_hurtDistanceX = 0;
	m_hurtDistanceY = 0;
	m_hp = 100;
}


CharacterObject::~CharacterObject()
{
}

PlayerState* CharacterObject::GetCurrentState(int currentState) {
	switch (currentState) {
	case 0:
		return Stand;
	case 1:
		return Left;
	case 2:
		return Right;
	case 3:
		return Defense;
	case 4:
		return BreakDefense;
	case 5:
		return Attack;
	case 6:
		return SecondAttack;
	case 7:
		return ThirdAttack;
	case 8:
		return Teleport;
	case 9:
		return UpAttack;
	case 10:
		return Jump;
	case 11:
		return AirAttack;
	case 12:
		return Hurt;
	case 13:
		return KnockedDownGetUp;
	case 14:
		return Celebrate;
	case 15:
		return GetReady;
	case 16:
		return ThoundsPain;
	}
	return NULL;
}

int CharacterObject::GetDefenseCentreX() {
	int defenseCentreX = m_direction ? (m_dX + m_iDrawWidth - m_defenseX - m_defenseW / 2) : (m_dX + m_defenseX + m_defenseW / 2);
	return defenseCentreX;
}

void CharacterObject::BeAttacked(int state, int damage, int time, int dX, int dY) {
	if ((m_currentStateId == 13) || ((m_currentStateId == 8) && (m_currentFrame == 1))){
		return;
	}
	if ((m_defense) && (state == 12)){
		return;
	}

	m_currentStateId = state;
	m_currentState = GetCurrentState(m_currentStateId);
	m_counter = 0;
	m_currentFrame = 0;

	if (state == 12) {
		int duration[20];
		for (int i = 0; i < 20; i++) {
			duration[i] = -1;
		}
		duration[0] = time;
		Hurt->SetDuration(duration);
	}

	m_hurtDistanceX = dX;
	m_hurtDistanceY = dY;
	
	m_hp -= damage;
	if (m_hp <= 0) {
		m_hp = 0;

		m_currentStateId = 13;
		m_currentState = GetCurrentState(m_currentStateId);
		m_counter = 0;
		m_currentFrame = 0;

		int duration[20];
		for (int i = 0; i < 20; i++) {
			duration[i] = 4;
		}
		duration[3] = -1;
		KnockedDownGetUp->SetDuration(duration);
	}

	return;
}

void CharacterObject::InputControl() {
	int state = m_currentStateId;
	if (m_currentState->GetControl() && (!m_landing)) {
		if (!m_air) {
			state = 0;
			// <-
			if (((GetEngine()->IsKeyPressed(SDLK_a)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_LEFT)) && (m_playerId == 2))) {
				state = 1;
				m_direction = 1;
			}

			// ->
			if (((GetEngine()->IsKeyPressed(SDLK_d)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_RIGHT)) && (m_playerId == 2))) {
				state = 2;
				m_direction = 0;
			}

			// teleport
			if (((GetEngine()->IsKeyPressed(SDLK_l)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_KP_3)) && (m_playerId == 2))) {
				state = 8;
			}

			// jump
			if (((GetEngine()->IsKeyPressed(SDLK_k)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_KP_2)) && (m_playerId == 2))) {
				state = 10;
			}

			// defense
			if (((GetEngine()->IsKeyPressed(SDLK_s)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_DOWN)) && (m_playerId == 2))) {
				state = 3;
			}

			// attack
			if (((GetEngine()->IsKeyPressed(SDLK_j)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_KP_1)) && (m_playerId == 2))) {
				state = 5;
			}

			// up +¡¡Attack
			if ((state == 5) && ((GetEngine()->IsKeyPressed(SDLK_w) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_UP) && (m_playerId == 2))))) {
				state = 9;
			}

			// down +¡¡Attack
			if ((state == 5) && ((GetEngine()->IsKeyPressed(SDLK_s) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_DOWN) && (m_playerId == 2))))) {
				state = 4;
			}
		}
		else {
			state = 10;
			// <-
			if (((GetEngine()->IsKeyPressed(SDLK_a)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_LEFT)) && (m_playerId == 2))) {
				state = 1;
			}

			// ->
			if (((GetEngine()->IsKeyPressed(SDLK_d)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_RIGHT)) && (m_playerId == 2))) {
				state = 2;
			}

			// teleport
			if ((m_dSY < 0) && (((GetEngine()->IsKeyPressed(SDLK_l)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_KP_3)) && (m_playerId == 2)))) {
				state = 8;
			}

			// air Attack
			if (((GetEngine()->IsKeyPressed(SDLK_j)) && (m_playerId == 1))
				|| ((GetEngine()->IsKeyPressed(SDLK_KP_1)) && (m_playerId == 2))) {
				state = 11;
			}
		}
	}

	if ((m_currentFrame == m_currentState->GetWait()) &&
		((GetEngine()->IsKeyPressed(SDLK_j) && (m_playerId == 1)) || ((GetEngine()->IsKeyPressed(SDLK_KP_1)) && (m_playerId == 2)))) {
		state++;
	}

	if (state != m_currentStateId) {
		m_currentStateId = state;
		m_currentState = GetCurrentState(m_currentStateId);
		m_counter = 0;
		m_currentFrame = 0;
	}

	return ;
}

bool CharacterObject::IfRectangleIntersect(int centreX1, int centreY1, int w1, int h1, int X2, int Y2, int w2, int h2) {
	int screenX = X2 - w1 / 2;
	int screenY = Y2 - h1 / 2;

	return ((centreX1 > screenX) && (centreX1 < screenX + w2 + w1) && (centreY1 > screenY) && (centreY1 < screenY + h2 + h1));
}

void CharacterObject::CheckDirection() {
	if ((m_pEngine->GetState() != 2) && (m_pEngine->GetState() != 5)) {
		return;
	}

	if ((m_currentState->GetControl()) && (!m_air) && (!m_landing)) {
		CharacterObject* enemy;
		enemy = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId % 2));

		m_direction =  (enemy->GetXCentre() > GetXCentre()) ? 0 : 1;
	}
	return;
}

bool CharacterObject::CheckAttack() {
	return (m_attackH > 0);
}

void CharacterObject::CrackTile() {
	FightTileManager& tileManager = m_pEngine->GetTileManager();
	if (m_direction == 0) {
		tileManager.BeCracked(GetEngine(), m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight);
	}
	else {
		tileManager.BeCracked(GetEngine(), m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight);
	}
}

void CharacterObject::CheckPosition() {
	if (m_currentStateId == 16) {
		return;
	}

	FightTileManager& tileManager = m_pEngine->GetTileManager();
	int iPX = tileManager.GetTileXForPositionOnScreen(m_dX + m_iDrawWidth / 2);
	int iPY = tileManager.GetTileYForPositionOnScreen(m_dY + m_iDrawHeight);
	if (tileManager.GetValue(iPX, iPY) == 1) {
		m_dY = iPY * tileManager.GetTileHeight() + 20 - m_iDrawHeight;
	}

	if (m_dY < 100) {
		m_dY = 100;
	}

	int mapX = m_direction ? m_dX + m_iDrawWidth - m_defenseW - m_defenseX : m_dX + m_defenseX;
	int mapY = m_dY + m_defenseY;

	int temp = -1;
	if (mapX < 0) {
		m_dX = m_direction ? m_defenseW + m_defenseX - m_iDrawWidth : -m_defenseX;
		temp = 0;
	}

	if (mapX + m_defenseW > GetEngine()->GetScreenWidth() - 1) {
		m_dX = m_direction ? GetEngine()->GetScreenWidth() - m_iDrawWidth + m_defenseX : GetEngine()->GetScreenWidth() - m_defenseX - m_defenseW;
		temp = 1;
	}

	if (m_pEngine->GetState() != 2) {
		return;
	}

	CharacterObject* enemy;
	enemy = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId % 2));

	if ((m_currentStateId == 8) || (enemy->GetState() == 8)) {
		return;
	}
	
	int centreX = enemy->GetDefenseCentreX();
	int centreY = enemy->GetDefenseCentreY();
	int w1 = enemy->GetDefenseW();
	int h1 = enemy->GetDefenseH();
	
	if (IfRectangleIntersect(centreX, centreY, w1, h1, mapX, mapY, m_defenseW, m_defenseH)) {
		if (temp == 0) {
			m_dX = m_direction ? centreX + w1 / 2 - m_iDrawWidth + m_defenseX + m_defenseW :
				centreX + w1 / 2 - m_defenseX;

			return;
		}
		if (temp == 1) {
			m_dX = m_direction ? centreX - w1 / 2 - m_iDrawWidth + m_defenseX :
				centreX - w1 / 2 - m_defenseW - m_defenseX;
			
			//m_dY = 740 - m_defenseH - m_defenseY;

			return;
		}

		if (mapX + m_defenseW / 2 < centreX) {
			m_dX = m_direction ? centreX - w1 / 2 - m_iDrawWidth + m_defenseX :
				centreX - w1 / 2 - m_defenseW - m_defenseX;
		}
		else {
			m_dX = m_direction ? centreX + w1 / 2 - m_iDrawWidth + m_defenseX + m_defenseW :
				centreX + w1 / 2 - m_defenseX;
		}
		
	}
}

void CharacterObject::ChangeState(int state) {
	if (m_currentStateId == state) {
		return;
	}

		m_currentStateId = state;
		m_drawStateId = m_currentStateId;
		m_currentState = GetCurrentState(m_currentStateId);
		m_currentFrame = 0;
		m_counter = 0;
}

void CharacterObject::CelebratePose() {
	if ((m_currentState->GetControl()) && (!m_air) && (!m_landing)){
		m_currentStateId = 14;
		m_currentState = GetCurrentState(m_currentStateId);
		m_currentFrame = 0;
		m_counter = 0;
	}
}

