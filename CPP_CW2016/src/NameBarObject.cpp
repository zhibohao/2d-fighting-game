#include "header.h"
#include "NameBarObject.h"
#include "CharacterObject.h"

NameBarObject::NameBarObject(BaseEngine* pEngine, int playerId)
	:DisplayableObject(pEngine), m_playerId(playerId)
{
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	
	m_color = (m_playerId == 1) ? 0XF44336 : 0X2196F3;

	CharacterObject* currentCharacter = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId - 1));
	m_iPreviousScreenX = m_iCurrentScreenX = currentCharacter->GetDefenseCentreX() - currentCharacter->GetDefenseW() / 2 + 20;
	m_iPreviousScreenY = m_iCurrentScreenY = currentCharacter->GetDefenseCentreY() - currentCharacter->GetDefenseH() / 2 - 150;
	
	if (currentCharacter->GetType() == 0) {
		m_iPreviousScreenY -= 6;
		m_iCurrentScreenY -= 6;
	}
	
	m_iDrawWidth = 100;
	m_iDrawHeight = 90;

	SetVisible(true);
}


NameBarObject::~NameBarObject()
{
}

void NameBarObject::Draw() {
	//GetEngine()->DrawScreenRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth - 1, m_iCurrentScreenY + m_iDrawHeight - 1, 0);

	char buffer[32];
	sprintf(buffer, "P%d", m_playerId);
	GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buffer, m_color, GetEngine()->GetFont("Cornerstone Regular.ttf", 40));

	GetEngine()->DrawScreenTriangle(m_iCurrentScreenX, m_iCurrentScreenY + 50, 
		m_iCurrentScreenX + 50, m_iCurrentScreenY + 50, 
		m_iCurrentScreenX + 25, m_iCurrentScreenY + 25 + 55,
		m_color);

	StoreLastScreenPositionForUndraw();
}

void NameBarObject::DoUpdate(int iCurrentTime) {
	CharacterObject* currentCharacter = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId - 1));
	m_iCurrentScreenX = currentCharacter->GetDefenseCentreX() - currentCharacter->GetDefenseW() / 2 + 20;
	m_iCurrentScreenY = currentCharacter->GetDefenseCentreY() - currentCharacter->GetDefenseH() / 2 - 150;
	
	if (currentCharacter->GetType() == 0) {
		m_iCurrentScreenY -= 6;
	}
	
	RedrawObjects();
}