#include "Tilemap.h"
#include "Config.h"
#include "Renderer.h"
#include "game.h"
#include "Floor.h"

Tilemap::Tilemap(int tilemapX, int tilemapY)
	: SDLGameObject(true), m_tilemapX(tilemapX), m_tilemapY(tilemapY)
{
	m_tilemap = new int* [tilemapY];

	for (int i = 0; i < tilemapY; i++)
	{
		m_tilemap[i] = new int [tilemapX];
	}
}

Tilemap::~Tilemap()
{
	cleanup();
}

void Tilemap::draw()
{
	SDL_Rect destRect;

	// Calculate screen bounds to skip drawing tiles that are not visible
	int screenX = game::Instance()->getCameraPos().x / TILE_SIZE;
	int screenY = game::Instance()->getCameraPos().y / TILE_SIZE;
	int screenW = SCREEN_WIDTH / TILE_SIZE + 1; // +1 to draw tiles that are partially visible
	int screenH = SCREEN_HEIGHT / TILE_SIZE + 1; // +1 to draw tiles that are partially visible

	// Nested for loop to iterate over each tile in m_tilemap
	for (int y = screenY; y < screenY + screenH; y++)
	{
		for (int x = screenX; x < screenX + screenW; x++)
		{
			// Check if drawing tile is within bounds of m_tilemap
			if (x < 0 || x > m_tilemapX || y < 0 || y > m_tilemapY)
				continue;

			// If the tile is a floor, draw it
			if (m_tilemap[y][x] == FLOOR)
			{
				// Calculate the destination rectangle offset by the camera position
				destRect.x = x * TILE_SIZE - game::Instance()->getCameraPos().x;
				destRect.y = y * TILE_SIZE - game::Instance()->getCameraPos().y;
				destRect.w = TILE_SIZE;
				destRect.h = TILE_SIZE;
				SDL_RenderCopy(game::Instance()->getRenderer(), Renderer::getTexture("floor"), NULL, &destRect);
			}
		}
	}
}

void Tilemap::update()
{
}

void Tilemap::cleanup()
{
	printf("Tilemap cleaning up...\n");
	// Delete the 2D array
	for (int i = 0; i < m_tilemapY; i++)
	{
		delete[] m_tilemap[i];
	}
	delete[] m_tilemap;

	m_tilemap = nullptr;
}

void Tilemap::setTile(int x, int y, TileType tileType)
{
	m_tilemap[y][x] = tileType;
}