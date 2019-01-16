#pragma once
#include "DisplayableObject.h"
class NameBarObject :
	public DisplayableObject
{
public:
	NameBarObject(BaseEngine* pEngine, int playerId);
	~NameBarObject();

	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	int m_playerId;
	int m_color;
};

