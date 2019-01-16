#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "FightEngine.h"

class BackgroundControl :
	public DisplayableObject
{
public:
	BackgroundControl(FightEngine* pEngine);
	~BackgroundControl();

	void Draw();
	void DoUpdate(int iCurrentTime);
	void BackgroundTransition(int scene);
	bool IsFinish() { return m_finish; };
	int GetScene() { return m_scene; };
	void MoveBackground(int direction);

private:
	ImageData m_transition;
	ImageData m_background;

	ImageData m_background1;
	ImageData m_background2;

	FightEngine* m_pEngine;
	int m_dX;
	bool m_finish;
	int m_scene;
	int m_teachBackground1;
	int m_teachBackground2;
};

