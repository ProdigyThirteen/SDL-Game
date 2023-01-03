#pragma once
#include "SDLGameObject.h"
class Floor : public SDLGameObject
{
private:
	SDL_Texture* m_tilemap;

public:
	Floor(const AssetLoader* pParams);
	void draw();
	void update();
	void cleanup() override;
};

