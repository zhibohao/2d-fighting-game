#include "header.h"
#include "BirdObject.h"

BirdObject::BirdObject(FightEngine *pEngine)
	:CharacterObject(pEngine)
{
	m_iStartDrawPosX = m_iStartDrawPosY = 0;
	m_iDrawHeight = m_iDrawWidth = 60;

	m_dX = 200;
	m_dY = 50;

	m_iPreviousScreenX = m_iCurrentScreenX = m_dX;
	m_iPreviousScreenY = m_iCurrentScreenY = m_dY;

	m_direction = 0;
	m_currentStateId = 2;
	m_counter = 0;
	m_currentFrame = 0;
	m_currentState = GetCurrentState(m_currentStateId);

	m_image.LoadImage("../Image/Bird.png");

	SetState();

	SetVisible(true);
}


BirdObject::~BirdObject()
{
}

void BirdObject::SetState() {
	Left->SetNumberFrame(5);
	Right->SetNumberFrame(5);
	Hurt->SetNumberFrame(1);

	int duration[20];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 20; j++) {
			duration[j] = -1;
		}
		switch (i) {
		case 0:
			duration[0] = 5;
			duration[1] = 5;
			duration[2] = 5;
			duration[3] = 5;
			duration[4] = 5;
			GetCurrentState(1)->SetDuration(duration);
			GetCurrentState(2)->SetDuration(duration);
			break;
		case 1:
			duration[0] = -1;
			GetCurrentState(12)->SetDuration(duration);
			break;
		}
	}
}

void BirdObject::Draw() {
	if (!IsVisible()) {
		return;
	}

	int duration = m_currentState->GetDuration(m_currentFrame);
	int numberFrame = m_currentState->GetNumberFrame();
	int row;
	switch (m_currentStateId) {
	case 1:
		row = 0;
		break;
	case 2:
		row = 1;
		break;
	case 12:
		row = 2;
		break;
	}

	m_image.RenderImageWithMask(m_pEngine->GetSDLSurface(),
		m_currentFrame * m_iDrawWidth, row * m_iDrawHeight,
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iDrawWidth, m_iDrawHeight);

	StoreLastScreenPositionForUndraw();
}

void BirdObject::MoveControl() {
	switch (m_currentStateId) {
	case 1:
	case 2:
		m_dX = m_direction ? m_dX - 3 : m_dX + 3;
		break;
	case 12:
		m_direction = 0;
		break;
	}
}

void BirdObject::CheckFrame() {
	m_counter++;
	int duration = m_currentState->GetDuration(m_currentFrame);
	int numberFrame = m_currentState->GetNumberFrame();

	if ((m_counter > duration) && (duration != -1)) {
		m_counter = 1;
		m_currentFrame = (m_currentState->GetControl() && !m_landing) ? (m_currentFrame + 1) % numberFrame : m_currentFrame + 1;
	}

}

void BirdObject::CheckPosition() {
	if (m_dX < 0) {
		m_dX = 0;
		m_direction = 0;
		ChangeState(2);
	}
	if (m_dX + m_iDrawWidth > m_pEngine->GetScreenWidth()) {
		m_dX = m_pEngine->GetScreenWidth() - m_iDrawWidth;
		m_direction = 1;
		ChangeState(1);
	}
}

void BirdObject::DoUpdate(int iCurrentTime) {
	CheckFrame();

	MoveControl();

	CheckPosition();

	m_iCurrentScreenX = m_dX;
	m_iCurrentScreenY = m_dY;

	RedrawObjects();
}