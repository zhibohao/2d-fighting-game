#include "header.h"
#include "KakashiObject.h"
#include "BackgroundControl.h"


KakashiObject::KakashiObject(FightEngine *pEngine, int playerId)
	:CharacterObject(pEngine)
{
	m_playerId = playerId;
	m_dX = 800;
	m_dY = 540;

	m_iPreviousScreenX = m_iCurrentScreenX = m_dX;
	m_iPreviousScreenY = m_iCurrentScreenY = m_dY;

	m_iDrawWidth = m_iDrawHeight = 100 * 2;

	m_direction = m_playerId - 1;

	m_image.LoadImage("../Image/Kakashi.png");
	m_dialog.LoadImage("../Image/DialogBox.png");
	m_button.LoadImage("../Image/KeyButton.png");

	m_state = 0;
	m_finished = false;

	SetState();

	SetVisible(true);
}

KakashiObject::~KakashiObject()
{
}

void KakashiObject::SetState() {
	Stand = new PlayerState(0);
	Read = new PlayerState(0);
	PoseGO = new PlayerState(0);
	SennenGoroshi = new PlayerState(0);

	Stand->SetNumberFrame(3);
	Read->SetNumberFrame(2);
	PoseGO->SetNumberFrame(2);
	SennenGoroshi->SetNumberFrame(6);

	Stand->SetControl(true);
	Read->SetControl(false);
	PoseGO->SetControl(false);
	SennenGoroshi->SetControl(false);

	int duration[20];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 20; j++) {
			duration[j] = -1;
		}
		switch (i)
		{
		case 0:
			duration[0] = -2;
			duration[1] = 30;
			duration[2] = 30;
			break;
		case 1:
			duration[0] = 30;
			duration[1] = 120;
			break;
		case 2:
			duration[0] = 10;
			duration[1] = 140;
			break;
		case 3:
			duration[0] = 25;
			duration[1] = 8;
			duration[2] = 10;
			duration[3] = 12;
			duration[4] = 8;
			duration[5] = 30;
			break;
		}
		GetCurrentState(i)->SetDuration(duration);
	}

	for (int i = 0; i < 20; i++) {
		m_duration[i] = -1;
	}
	m_duration[0] = 60;
	m_duration[1] = 140;
	m_duration[11] = 140;
	m_duration[12] = 140;
	m_duration[14] = 140;
	m_durationCounter = 0;

	return;
}

PlayerState* KakashiObject::GetCurrentState(int currentState) {
	switch (currentState) {
	case 0:
		return Stand;
	case 1:
		return Read;
	case 2:
		return PoseGO;
	case 3:
		return SennenGoroshi;
	}
	return NULL;
}

void KakashiObject::ChangeState(int state) {
	if (m_currentStateId == state) {
		return;
	}

	m_currentStateId = state;
	m_drawStateId = m_currentStateId;
	m_currentState = GetCurrentState(m_currentStateId);
	m_currentFrame = 0;
	m_counter = 0;
}

void KakashiObject::Draw() {
	if (!IsVisible()) {
		return;
	}

	PlayerState* drawState = GetCurrentState(m_drawStateId);
	int duration = drawState->GetDuration(m_currentFrame);
	int numberFrame = drawState->GetNumberFrame();
	int offset = m_direction ? numberFrame : 0;

	m_image.RenderImageWithMask(m_pEngine->GetSDLSurface(),
		(m_currentFrame + offset) * m_iDrawWidth, m_drawStateId * m_iDrawHeight + 1,
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iDrawWidth, m_iDrawHeight);

	if ((m_state > 0) && (m_state < 14)) {
		m_pEngine->CopyBackgroundPixels(m_iCurrentScreenX - 120, m_iCurrentScreenY - 230, 340, 200);

		m_dialog.RenderImageWithMask(m_pEngine->GetSDLSurface(),
			0, 0,
			m_iCurrentScreenX - 150, m_iCurrentScreenY - 250,
			m_dialog.GetWidth(), m_dialog.GetHeight());

		//m_pEngine->DrawScreenRectangle(m_iCurrentScreenX - 120, m_iCurrentScreenY - 230,
		//	m_iCurrentScreenX - 120 + 340, m_iCurrentScreenY - 230 + 200, 0xff0000);
	
		m_pEngine->DrawScreenString(m_iCurrentScreenX - 80, m_iCurrentScreenY - 180, m_word1, 0, NULL);
		m_pEngine->DrawScreenString(m_iCurrentScreenX - 80, m_iCurrentScreenY - 120, m_word2, 0, NULL);

		int tempX, tempY;
		switch (m_state) {
		case 2:
			tempX = 1;
			tempY = 0;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52 , tempY * 57,
				m_iCurrentScreenX + 20, m_iCurrentScreenY - 200, 52, 57);

			tempX = 3;
			tempY = 0;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 130, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 3:
			tempX = 1;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 4:
			tempX = 2;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 6:
			tempX = 2;
			tempY = 0;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 7:
			tempX = 0;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 8:
			tempX = 0;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20 + 155, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 9:
			tempX = 0;
			tempY = 0;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20 - 30, m_iCurrentScreenY - 200, 52, 57);
			tempX = 0;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 130 - 30, m_iCurrentScreenY - 200, 52, 57);
			break;
		case 10:
			tempX = 2;
			tempY = 0;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 20 + 20, m_iCurrentScreenY - 200, 52, 57);
			tempX = 0;
			tempY = 1;
			m_button.RenderImageWithMask(m_pEngine->GetSDLSurface(), tempX * 52, tempY * 57,
				m_iCurrentScreenX + 130+ 20, m_iCurrentScreenY - 200, 52, 57);
			break;
		}
	}

	StoreLastScreenPositionForUndraw();
}

void KakashiObject::CheckFrame() {
	m_counter++;
	m_drawStateId = m_currentStateId;
	int duration = GetCurrentState(m_drawStateId)->GetDuration(m_currentFrame);
	int numberFrame = GetCurrentState(m_drawStateId)->GetNumberFrame();

	if ((m_counter > duration) && (duration >= 0)) {
		m_counter = 1;
		m_currentFrame = m_currentState->GetControl() ? (m_currentFrame + 1) % numberFrame : m_currentFrame + 1;
	}

	if ((duration == -2) && (m_counter > 50)) {
		int temp = rand() % 100;
		if (temp == 0) {
			ChangeState(0);
			m_currentFrame++;
		}

		if (temp == 1) {
			ChangeState(1);
		}
	}

	if (m_currentFrame >= numberFrame) {

		m_currentStateId = 0;
		m_drawStateId = m_currentStateId;
		m_currentState = GetCurrentState(m_currentStateId);
		m_currentFrame = 0;
		m_counter = 1;
	}
}

/*
	0	Wait
	1	Introduce
	2	Move a / d -> 1 || 2
	3	Jump k -> 10
	4	Teleport -> 8
	5	Teleporu in the air -> 8 && air
	6	Defense -> 3
	7	Attack -> 5
	8	Multiple Attack -> 7
	9	Up Attack -> 9
	10	Down Attack  Air Attack -> 4 || 11
	13	Get Ready -> 15
*/
void KakashiObject::CheckState() {
	CharacterObject* currentCharacter = dynamic_cast<CharacterObject*>(m_pEngine->GetDisplayableObject(0));
	int characterState = currentCharacter->GetState();

	switch (m_state) {
	case 2:
		if (characterState == 2) {
			m_finished = true;
		}
		break;
	case 3:
		if (characterState == 10) {
			m_finished = true;
		}
		break;
	case 4:
		if (characterState == 8) {
			m_finished = true;
		}
		break;
	case 5:
		if ((characterState == 8) && (currentCharacter->GetAir())) {
			m_finished = true;
		}
		break;
	case 6:
		if (characterState == 3) {
			m_finished = true;
		}
		break;
	case 7:
		if (characterState == 5) {
			m_finished = true;
		}
		break;
	case 8:
		if (characterState == 7) {
			m_finished = true;
		}
		break;
	case 9:
		if (characterState == 9) {
			m_finished = true;
		}
		break;
	case 10:
		if (characterState == 11) {
			m_finished = true;
		}
		break;
	case 13:
		if (characterState == 15) {
			m_finished = true;
		}
		break;
	}
	return;
}

void KakashiObject::DrawBackground() {
	ImageData NarutoBackground;
	NarutoBackground.LoadImage("../Image/NarutoBackground.png");
	NarutoBackground.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, 680, 582, NarutoBackground.GetWidth(), NarutoBackground.GetHeight());
}

void KakashiObject::CheckNaturo() {
	CharacterObject* Naruto = dynamic_cast<CharacterObject*>(m_pEngine->GetDisplayableObject(0));
	if (Naruto->GetState() == 16) {
		if (Naruto->GetXCentre() < m_pEngine->GetScreenWidth()) {
			return;
		}
		else {
			Naruto->SetVisible(false);
			m_pEngine->SetState(4);
			BackgroundControl* backgroundControl = dynamic_cast<BackgroundControl*> (m_pEngine->GetDisplayableObject(3));
			backgroundControl->BackgroundTransition(2);
			m_state++;
			return;
		}
	}

	if ((Naruto->GetXCentre() > 720) && (Naruto->GetXCentre() < 760) && (Naruto->GetState() < 3) && (!Naruto->GetAir())) {
		Naruto->ChangeState(15);
	}

}

void KakashiObject::CheckDialog() {
	m_durationCounter++;
	if ((m_durationCounter > m_duration[m_state]) && (m_duration[m_state] > 0)) {
		m_state++;
		m_durationCounter = 0;
	}

	if (m_duration[m_state] < 0) {
		if (!m_finished) {
			CheckState();
		}

		if (m_finished) {
			m_state++;
			m_durationCounter = 0;
			m_finished = false;
		}
	}

	switch (m_state) {
	case 1:
		sprintf(m_word1, "I will teach you how");
		sprintf(m_word2, "to fight. Naruto!");
		break;
	case 2:
		sprintf(m_word1, "Press       /");
		sprintf(m_word2, "to Move.");
		break;
	case 3:
		sprintf(m_word1, "Press");
		sprintf(m_word2, "to Jump.");
		break;
	case 4:
		sprintf(m_word1, "Press");
		sprintf(m_word2, "to Teleport.");
		break;
	case 5:
		sprintf(m_word1, "You can Teleport");
		sprintf(m_word2, "when you Jump.");
		break;
	case 6:
		sprintf(m_word1, "Press");
		sprintf(m_word2, "to Defense.");
		break;
	case 7:
		sprintf(m_word1, "Press");
		sprintf(m_word2, "to Attack.");
		break;
	case 8:
		sprintf(m_word1, "Continuous press");
		sprintf(m_word2, "to Multiple Attacks.");
		break;
	case 9:
		sprintf(m_word1, "Try       +");
		sprintf(m_word2, "");
		break;
	case 10:
		sprintf(m_word1, "Rember       +");
		sprintf(m_word2, "and Attack in the air");
		break;
	case 11:
		sprintf(m_word1, "can help you");
		sprintf(m_word2, "to break Defense");
		break;
	case 12:
		sprintf(m_word1, "Let's bring Sasuke");
		sprintf(m_word2, "Back! Naruto!");
		m_direction = 0;
		ChangeState(2);
		break;
	case 13:
		sprintf(m_word1, "If you are ready,");
		sprintf(m_word2, "come here.");
		DrawBackground();
		CheckNaturo();
		break;
	case 14:
		CheckNaturo();
		if (m_durationCounter == 0) {
			sprintf(m_word1, "");
			sprintf(m_word2, "");
			m_pEngine->Redraw(true);
		}
		break;
	case 15:
		CheckNaturo();
		if (m_durationCounter == 0) {
			ChangeState(3);
		}

		break;
	}
}

void KakashiObject::MoveControl() {
	if (m_currentStateId != 3) {
		return;
	}

	switch (m_currentFrame) {
	case 2:
		if (m_counter == 5) {
			m_dX = 540;
			m_direction = 0;
		}
		break;
	case 5:
		if (m_counter == 1) {
			CharacterObject* Naruto = dynamic_cast<CharacterObject*>(m_pEngine->GetDisplayableObject(0));
			Naruto->ChangeState(16);
			CharacterObject* Bird = dynamic_cast<CharacterObject*>(m_pEngine->GetDisplayableObject(2));
			Bird->ChangeState(12);
		}

		break;
	}

	m_iCurrentScreenX = m_dX;
}

void KakashiObject::DoUpdate(int iCurrnetTime) {

	CheckDirection();

	CheckDialog();

	CheckFrame();
	MoveControl();

	RedrawObjects();
}
