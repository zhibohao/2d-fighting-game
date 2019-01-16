#pragma once
#include "TileManager.h"
#include "JPGImage.h"

class FightTileManager :
	public TileManager
{
public:
	FightTileManager();
	~FightTileManager();
	void BeCracked(BaseEngine* pEngine, int dX, int dY);
	void RepairTile();
	int GetCol() { return m_col; };
	int GetRow() { return m_row; };


	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

private:
	ImageData m_image;
	BaseEngine* m_pEngine;

	int m_counter[50][50];
	int m_row;
	int m_col;
};

