#include "header.h"
#include "SasukeObject.h"

SasukeObject::SasukeObject(FightEngine* pEngine, int playerId)
	:CharacterObject(pEngine)
{
	m_playerId = playerId;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = 100 * 2;
	m_iDrawHeight = 100 * 2;

	m_dX = m_playerId == 1 ? 200 : 900;
	m_dY = 400;
	m_air = true;

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

	SetVisible(true);
}


SasukeObject::~SasukeObject()
{
}

void SasukeObject::SetState() {
	int duration[20];

	Stand->SetNumberFrame(6);
	ThirdAttack->SetNumberFrame(5);
	KnockedDownGetUp->SetNumberFrame(7);

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 20; j++) {
			duration[j] = -1;
		}
		switch (i)
		{
		case 0:
			duration[0] = 5;
			duration[1] = 5;
			duration[2] = 5;
			duration[3] = 5;
			duration[4] = 5;
			duration[5] = 5;
			break;
		case 1:
			duration[0] = 6;
			duration[1] = 6;
			duration[2] = 6;
			duration[3] = 6;
			duration[4] = 6;
			duration[5] = 6;
			break;
		case 2:
			duration[0] = 6;
			duration[1] = 6;
			duration[2] = 6;
			duration[3] = 6;
			duration[4] = 6;
			duration[5] = 6;
			break;
		case 3:
			duration[0] = -1;
			break;
		case 4:
			duration[0] = 12;
			duration[1] = 8;
			duration[2] = 8;
			duration[3] = 2;
			duration[4] = 20;
			break;
		case 5:
			duration[0] = 4;
			duration[1] = 8;
			duration[2] = 10;
			break;
		case 6:
			duration[0] = 4;
			duration[1] = 8;
			duration[2] = 10;
			break;
		case 7:
			duration[0] = 3;
			duration[1] = 3;
			duration[2] = 14;
			duration[3] = 4;
			duration[4] = 20;
			break;
		case 8:
			duration[0] = 6;
			duration[1] = 10;
			duration[2] = 6;
			break;
		case 9:
			duration[0] = 8;
			duration[1] = 8;
			duration[2] = 8;
			break;
		case 10:
			duration[0] = -1;
			duration[1] = -1;
			duration[2] = 6;
			break;
		case 11:
			duration[0] = 12;
			duration[1] = -1;
			duration[2] = 4;
			duration[3] = 4;
			duration[4] = 20;
			break;
		case 12:
			duration[0] = -1;
			break;
		case 13:
			duration[0] = 4;
			duration[1] = 4;
			duration[2] = 4;
			duration[3] = 22;
			duration[4] = 8;
			duration[5] = 8;
			duration[6] = 8;
			break;
		case 14:
			duration[0] = 10;
			duration[1] = 8;
			duration[2] = 18;
			break;
		}
		GetCurrentState(i)->SetDuration(duration);
	}
	return;

}

void SasukeObject::Draw() {
	if (!IsVisible()) {
		return;
	}

	PlayerState* drawState = GetCurrentState(m_drawStateId);
	int duration = drawState->GetDuration(m_currentFrame);
	int numberFrame = drawState->GetNumberFrame();
	int offset = 0;
	if ((m_drawStateId != 1) && (m_drawStateId != 2)){
		offset = m_direction ? numberFrame : 0;
	}

	m_image.RenderImageWithMask(m_pEngine->GetSDLSurface(),
		(m_currentFrame + offset) * m_iDrawWidth + 1, m_drawStateId * m_iDrawHeight + 1,
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iDrawWidth - 2, m_iDrawHeight);

	StoreLastScreenPositionForUndraw();
}

void SasukeObject::MoveControl(){
	int gravity = 1;
	if ((m_air) && (m_currentStateId != 8) && (m_currentStateId != 11) && (m_currentStateId != 9)) {
		m_dSY += gravity;
		m_dY += m_dSY;
	}

	m_defense = false;
	m_attackW = 0;
	m_attackH = 0;
	m_attackX = 0;
	m_attackY = 0;

	switch (m_currentStateId) {
	case 1:
		m_dX -= 13;
		break;
	case 2:
		m_dX += 13;
		break;
	case 3:
		m_defense = true;
		break;
	case 4:
		switch (m_currentFrame) {
		case 0:
			m_attackEnergy = 1;
			break;
		case 1:
			m_attackW = 42 * 2;
			m_attackH = 82 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 58 * 2 - m_attackW : 58 * 2;
			m_attackY = 9 * 2;

			m_dX = m_direction ? m_dX - 40 : m_dX + 40;
			break;
		case 2:
			m_attackW = 45 * 2;
			m_attackH = 22 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 55 * 2 - m_attackW : 55 * 2;
			m_attackY = 11 * 2;
			break;
		}
		break;
	case 5:
		switch (m_currentFrame) {
		case 0:
			m_attackEnergy = 1;
			break;
		case 1:
			m_dX = m_direction ? m_dX - 4 : m_dX + 4;
			m_attackW = 28 * 2;
			m_attackH = 14 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 63 * 2 - m_attackW : 63 * 2;
			m_attackY = 47 * 2;
			break;
		}
		break;
	case 6:
		switch (m_currentFrame) {
		case 0:
			m_attackEnergy = 1;
			break;
		case 1:
			m_dX = m_direction ? m_dX - 4 : m_dX + 4;
			m_attackW = 40 * 2;
			m_attackH = 14 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 60 * 2 - m_attackW : 60 * 2;
			m_attackY = 47 * 2;
			break;
		}
		break;
	case 7:
		switch (m_currentFrame) {
		case 0:
			m_attackEnergy = 1;
			break;
		case 2:
			m_dX = m_direction ? m_dX - 15 : m_dX + 15;

			m_attackW = 42 * 2;
			m_attackH = 22 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 57 * 2 - m_attackW : 57 * 2;
			m_attackY = 53 * 2;
			break;
		case 3:
			m_attackW = 42 * 2;
			m_attackH = 22 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 58 * 2 - m_attackW : 58 * 2;
			m_attackY = 53 * 2;
			break;
		}
		break;
	case 8:
		switch (m_currentFrame) {
		case 1:
			m_dX = m_direction ? m_dX - 35 : m_dX + 35;
			if (m_counter == 10) {
				m_dSY = 0;
			}
			break;
		}
		break;
	case 9:
		switch (m_currentFrame) {
		case 0:
			m_attackEnergy = 1;
			break;
		case 1:
			m_dX = m_direction ? m_dX - 8 : m_dX + 8;
			m_dY -= 25;
			m_air = true;
			m_attackW = 44 * 2;
			m_attackH = 43 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 55 * 2 - m_attackW : 55 * 2;
			m_attackY = 35 * 2;
			break;
		case 2:
			m_dX = m_direction ? m_dX - 2 : m_dX + 2;
			m_attackW = 43 * 2;
			m_attackH = 13 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 57 * 2 - m_attackW : 57 * 2;
			m_attackY = 38 * 2;
			if (m_counter == 8) {
				m_dSY = 0;
			}
			break;
		}
		break;
	case 10:
		if ((!m_air) && (!m_landing)) {
			m_air = true;
			m_dSY = -20;
			m_dY += m_dSY;
		}
		break;
	case 11:
		switch (m_currentFrame)
		{
		case 0:
			m_dSY = 0;

			m_attackEnergy = 1;
			break;
		case 1:
			m_dX = m_direction ? m_dX - 30 : m_dX + 30;
			m_dY += 30;

			m_attackW = 98 * 2;
			m_attackH = 28 * 2;
			m_attackX = m_direction ? m_iDrawWidth - 1 * 2 - m_attackW : 1 * 2;
			m_attackY = 45 * 2;
			break;
		}

		break;
	case 12:
		m_dX = m_direction ? m_dX + m_hurtDistanceX : m_dX - m_hurtDistanceX;
		m_dY += m_hurtDistanceY;
		if (m_hurtDistanceY < 0 && !m_air) {
			m_air = true;
		}
		if (m_counter == m_currentState->GetDuration(0)) {
			m_dSY = -1;
		}
		break;
	case 13:
		switch (m_currentFrame) {
		case 0:
		case 1:
		case 2:
			m_dX = m_direction ? m_dX + m_hurtDistanceX : m_dX - m_hurtDistanceX;
			break;
		case 6:
			m_dX = m_direction ? m_dX - 10 : m_dX + 10;
			break;
		}
		break;
	case 14:
		break;
	}
}

void SasukeObject::AttackJudgment() {

	if (m_attackEnergy <= 0) {
		return;
	}

	CharacterObject* enemy;
	enemy = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId % 2));

	if (IfRectangleIntersect(enemy->GetDefenseCentreX(), enemy->GetDefenseCentreY(), enemy->GetDefenseW(), enemy->GetDefenseH(), m_dX + m_attackX, m_dY + m_attackY, m_attackW, m_attackH)) {
		m_attackEnergy--;
		switch (m_currentStateId) {
		case 4:
		case 11:
			enemy->BeAttacked(13, 9, -1, 30, 0);
			break;
		case 5:
			enemy->BeAttacked(12, 5, 15, 3, 0);
			break;
		case 6:
			enemy->BeAttacked(12, 6, 20, 3, 0);
			break;
		case 7:
			enemy->BeAttacked(12, 8, 25, 20, 0);
			break;
		case 9:
			enemy->BeAttacked(12, 7, 15, 10, -20);
			break;
		};
	}
	
}

void SasukeObject::CheckFrame() {

	m_counter++;
	m_drawStateId = m_currentStateId;
	if (m_air && ((m_drawStateId == 1) || (m_drawStateId == 2))) {
		m_drawStateId = 10;
	}
	if ((m_drawStateId == 10) && (!m_landing)) {
		m_currentFrame = (m_dSY < 0) ? 0 : 1;
	}

	int duration = GetCurrentState(m_drawStateId)->GetDuration(m_currentFrame);
	int numberFrame = GetCurrentState(m_drawStateId)->GetNumberFrame();

	if ((m_counter > duration) && (duration != -1)) {
		m_counter = 1;
		m_currentFrame = (m_currentState->GetControl() && !m_landing) ? (m_currentFrame + 1) % numberFrame : m_currentFrame + 1;
		m_landing = false;
	}

	FightTileManager& tileManager = m_pEngine->GetTileManager();
	int iPX = tileManager.GetTileXForPositionOnScreen(m_dX + m_iDrawWidth / 2);
	int iPY = tileManager.GetTileYForPositionOnScreen(m_dY + m_iDrawHeight);
	if ((m_air) && (tileManager.GetValue(iPX, iPY) == 1)) {
		switch (m_drawStateId) {
		case 10:
			m_currentFrame = 2;
			break;
		case 11:
			m_currentFrame = 2;
			break;
		}
		m_air = false;
		m_landing = true;
		m_currentStateId = m_drawStateId;
		m_currentState = GetCurrentState(m_currentStateId);
		m_counter = 1;
		m_dSY = 0;
	}

	if (m_currentFrame >= numberFrame) {
		m_currentStateId = m_air ? 10 : 0;
		m_drawStateId = m_currentStateId;
		m_currentState = GetCurrentState(m_currentStateId);
		m_currentFrame = 0;
		m_counter = 1;
	}
	if ((m_drawStateId == 10) && (!m_landing)) {
		m_currentFrame = (m_dSY < 0) ? 0 : 1;
	}

}


void SasukeObject::DoUpdate(int iCurrentTime) {

	InputControl();

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