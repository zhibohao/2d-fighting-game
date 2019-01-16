#include "header.h"
#include "BackgroundControl.h"

/*
	m_scene
	0	menu -> select
	1	select -> menu
	2	select -> battle
	3	battle -> select
	4	menu -> teach
	5	menu -> record
*/

BackgroundControl::BackgroundControl(FightEngine* pEngine)
	:DisplayableObject(pEngine)
{
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iPreviousScreenX = m_iCurrentScreenX = 0;
	m_iPreviousScreenY = m_iCurrentScreenY = 0;
	m_iDrawWidth = 0;
	m_iDrawWidth = 0;

	m_dX = 0;

	m_pEngine = pEngine;
	m_teachBackground1 = 0;
	m_teachBackground2 = 0;

	m_finish = false;

	if (m_pEngine->GetState() == 5) {
		m_background1.LoadImage("../Image/TeachBackground1.png");
		m_background2.LoadImage("../Image/TeachBackground2.png");
	}

	SetVisible(false);
}


BackgroundControl::~BackgroundControl()
{
}

void BackgroundControl::Draw() {
	if (!IsVisible()) {
		return;
	}

	switch (m_scene) {
	case 0:
	case 5:
		m_background.RenderImageWithMask(GetEngine()->GetSDLSurface(), m_iCurrentScreenX, 0,
			m_iCurrentScreenX, m_iCurrentScreenY, m_background.GetWidth() - m_iCurrentScreenX, m_background.GetHeight());

		if (m_dX > 0) {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth(), m_transition.GetHeight());
		}
		else {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), -m_dX, 0,
				m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth() + m_dX, m_transition.GetHeight());
		}

		break;
	
	// TeachBackground
	case 4:
		m_background1.RenderImageWithMask(GetEngine()->GetSDLSurface(), m_iCurrentScreenX, 0,
			m_iCurrentScreenX, m_iCurrentScreenY, 1280 - m_iCurrentScreenX, m_background1.GetHeight());
		m_background2.RenderImageWithMask(GetEngine()->GetSDLSurface(), m_iCurrentScreenX, 0,
			m_iCurrentScreenX, m_iCurrentScreenY, 1280 - m_iCurrentScreenX, m_background2.GetHeight());

		if (m_dX > 0) {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth(), m_transition.GetHeight());
		}
		else {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), -m_dX, 0,
				m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth() + m_dX, m_transition.GetHeight());
		}

		break;
	case 1:
		m_background.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0,
			0, m_iCurrentScreenY, m_iCurrentScreenX, m_background.GetHeight());

		if (m_dX < 0) {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), -m_dX, 0,
				m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth() + m_dX, m_transition.GetHeight());
		}
		else {
			m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0,
				m_iCurrentScreenX, m_iCurrentScreenY, m_transition.GetWidth(), m_transition.GetHeight());
		}

		break;
	case 2:
		m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, m_dX,
			0, 0, 1280, 800);
		
		break;
	case 3:
		m_transition.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, m_dX,
			0, 0, 1280, 800);

		break;
	}

	StoreLastScreenPositionForUndraw();
}

void BackgroundControl::DoUpdate(int iCurrentTime) {
	if (!IsVisible()) {
		return;
	}

	switch (m_scene) {
	case 0:
	case 4:
	case 5:
		if (m_dX > -258) {
			m_dX -= 25;
			m_iCurrentScreenX -= 25;
			if (m_iCurrentScreenX < 0) {
				m_iCurrentScreenX = 0;
			}
		}
		else {
			m_finish = true;
		}

		break;
	case 1:

		if (m_dX < 1280) {
			m_dX += 25;
			m_iCurrentScreenX = m_dX;
			if (m_iCurrentScreenX < 0) {
				m_iCurrentScreenX = 0;
			}

		}
		else {
			m_finish = true;
		}

		break;
	case 2:
		if (m_dX + 800 < m_transition.GetHeight()) {
			m_dX += 15;
			if (m_dX + 800 > m_transition.GetHeight()) {
				m_dX = m_transition.GetHeight() - 800;
			}
		}
		else {
			m_finish = true;
		}

		break;
	case 3:
		if (m_dX > 0) {
			m_dX -= 15;
			if (m_dX < 0) {
				m_dX = 0;
			}
		}
		else {
			m_finish = true;
		}

		break;
	}

	RedrawObjects();
}

void BackgroundControl::BackgroundTransition(int scene) {
	m_scene = scene;

	switch (m_scene) {
	case 5:
	case 0:
		m_transition.LoadImage("../Image/Transition.png");
		m_background.LoadImage("../Image/SelectBackground.png");
		m_iPreviousScreenX = m_iCurrentScreenX = 1280;
		m_dX = 1280;
		break;
	case 1:
		m_transition.LoadImage("../Image/Transition.png");
		m_background.LoadImage("../Image/MenuBackground.png");
		m_iPreviousScreenX = m_iCurrentScreenX = 0;
		m_dX = -259;
		break;
	case 2:
		m_transition.LoadImage("../Image/BackgroundTransition.png");
		m_iPreviousScreenX = m_iCurrentScreenX = 0;
		m_dX = 0;
		break;
	case 3:
		m_transition.LoadImage("../Image/BackgroundTransition.png");
		m_iPreviousScreenX = m_iCurrentScreenX = 0;
		m_dX = m_transition.GetHeight() - 800;
		break;
	case 4:
		m_transition.LoadImage("../Image/Transition.png");
		m_background1.LoadImage("../Image/TeachBackground1.png");
		m_background2.LoadImage("../Image/TeachBackground2.png");
		m_iPreviousScreenX = m_iCurrentScreenX = 1280;
		m_dX = 1280;
		break;
	}

	m_iPreviousScreenY = m_iCurrentScreenY = 0;
	m_iDrawWidth = 1280;
	m_iDrawHeight = 800;

	SetVisible(true);
}

void BackgroundControl::MoveBackground(int direction) {
	int speed = 2;
	switch (direction) {
	case 1:
		if (m_teachBackground1 + speed < m_background1.GetWidth() - 1280) {	
			m_teachBackground1 += speed;
			m_background1.RenderImageWithMask(m_pEngine->GetBackground(), m_teachBackground1, 0, 0, 0, 1280, 800);
		}
		if (m_teachBackground2 + speed * 2 < m_background2.GetWidth() - 1280) {
			m_teachBackground2 += speed * 2;
			m_background2.RenderImageWithMask(m_pEngine->GetBackground(), m_teachBackground2, 0, 0, 0, 1280, 740);
		}
		break;
	case 0:
		if (m_teachBackground1 - speed >= 0) {
			m_teachBackground1 -= speed;
			m_background1.RenderImageWithMask(m_pEngine->GetBackground(), m_teachBackground1, 0, 0, 0, 1280, 800);
		}
		if (m_teachBackground2 - speed * 2 >= 0) {
			m_teachBackground2 -= speed * 2;
			m_background2.RenderImageWithMask(m_pEngine->GetBackground(), m_teachBackground2, 0, 0, 0, 1280, 740);
		}
		break;
	}
}