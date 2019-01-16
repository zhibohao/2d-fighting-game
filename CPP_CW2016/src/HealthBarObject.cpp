#include "header.h"
#include "HealthBarObject.h"
#include "CharacterObject.h"


HealthBarObject::HealthBarObject(BaseEngine* pEngine, int playerId)
	: DisplayableObject(pEngine), m_playerId(playerId), m_hp(100)
{
	switch (playerId) {
	case 1:
		m_iPreviousScreenX = m_iCurrentScreenX = 246;
		break;
	case 2:
		m_iPreviousScreenX = m_iCurrentScreenX = 734;
		break;
	}
	m_iPreviousScreenY = m_iCurrentScreenY = 95;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = 300;
	m_iDrawHeight = 14;

	SetVisible(true);
}


HealthBarObject::~HealthBarObject()
{
}

int HealthBarObject::CheckColor(int hp) {
	if (hp < 20) {
		return 0xf80000;
	}
	if (hp < 50){
		return 0xf8a800;
	}
	return 0x00b700;
}

void HealthBarObject::Draw(){
	if (!IsVisible()) {
		return;
	}
	
	switch (m_playerId) {
	case 1:
		GetEngine()->DrawScreenRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_hp * 3 + m_iCurrentScreenX - 1, m_iCurrentScreenY + m_iDrawHeight - 1,
			CheckColor(m_hp));
		break;
	case 2:
		GetEngine()->DrawScreenRectangle(m_iCurrentScreenX + (100 - m_hp) * 3, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth - 1, m_iCurrentScreenY + m_iDrawHeight - 1,
			CheckColor(m_hp));
		break;
	}

	StoreLastScreenPositionForUndraw();
}

void HealthBarObject::DoUpdate(int iCurrentTime) {

	CharacterObject* currentCharacter = dynamic_cast<CharacterObject*>(GetEngine()->GetDisplayableObject(m_playerId - 1));
	m_hp = currentCharacter->GetHp();

	RedrawObjects();
}