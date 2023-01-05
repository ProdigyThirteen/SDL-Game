#pragma once
#include "SDLGameObject.h"

enum TileType
{
	EMPTY = 0,
	WALL = 1,
	FLOOR = 2,
	CRATE = 3
};

class Tilemap : public SDLGameObject
{
private:
	const int m_tilemapX, m_tilemapY;
	int** m_tilemap;

	
public:
	Tilemap(int tilemapX, int tilemapY);
	~Tilemap();
	virtual void draw();
	virtual void update();
	virtual void cleanup();

	void setTile(int x, int y, TileType tileType);
};

