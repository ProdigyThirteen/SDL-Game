#include "UI.h"

void UI::createButton(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;

	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;

	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}