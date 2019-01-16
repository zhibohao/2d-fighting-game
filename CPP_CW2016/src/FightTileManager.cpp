#include "header.h"
#include "FightTileManager.h"

FightTileManager::FightTileManager()
	:TileManager(60, 60)
{
	m_image.LoadImage("../Image/Tile.png");
	m_row = 13;
	m_col = 22;
	for (int j = 0; j < m_row; j++) {
		for (int i = 0; i < m_col; i++) {
			m_counter[i][j] = 0;
		}
	}

	char* data[] = {
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"0000000000000000000000",
		"1111111111111111111111" };

	SetSize(m_col, m_row);

	for (int x = 0; x < m_col; x++) {
		for (int y = 0; y < m_row; y++) {
			SetValue(x, y, data[y][x] - '0');
		}
	}

	SetBaseTilesPositionOnScreen(0, 20);
}


FightTileManager::~FightTileManager()
{
}

void FightTileManager::RepairTile() {
	for (int j = 0; j < m_row; j++) {
		for (int i = 0; i < m_col; i++) {
			if (m_counter[i][j] > 0) {
				m_counter[i][j]--;
				if (m_counter[i][j] == 0) {
					int type = rand() % 5;

					m_image.RenderImageWithMask(m_pEngine->GetBackground(), type * GetTileWidth(), 0,
						i * GetTileWidth(), j * GetTileHeight() + 20, GetTileWidth(), GetTileHeight());
					m_pEngine->CopyBackgroundPixels(0, 740, m_pEngine->GetScreenWidth(), GetTileHeight());
				}
			}
		}
	}
	return;
}

void FightTileManager::BeCracked(BaseEngine* pEngine, int dX, int dY) {
	m_pEngine = pEngine;

	m_image.RenderImageWithMask(m_pEngine->GetBackground(), 5 * GetTileWidth(), 0, 
		GetTileXForPositionOnScreen(dX) * GetTileWidth(), dY, GetTileWidth(), GetTileHeight());
	m_pEngine->CopyBackgroundPixels(0, 740, m_pEngine->GetScreenWidth(), GetTileHeight());

	m_counter[GetTileXForPositionOnScreen(dX)][GetTileXForPositionOnScreen(dY)] = 100;
	return;
}

void FightTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const {

	switch (GetValue(iMapX, iMapY))
	{
	case 1:
		int type = rand() % 5;
		m_image.RenderImageWithMask(pSurface, type * GetTileWidth(), 0, iStartPositionScreenX, iStartPositionScreenY, GetTileWidth(), GetTileHeight());
		break;
	}
}