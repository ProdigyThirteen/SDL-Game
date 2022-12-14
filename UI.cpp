#include "UI.h"
#include "SDL_ttf.h"
#include "Renderer.h" // getRenderer

TTF_Font* UI::m_pFont = nullptr;
SDL_Renderer* UI::m_pRenderer = nullptr;

bool UI::init()
{
	m_pRenderer = Renderer::getRenderer();
	return true;
}

void UI::cleanup()
{
	TTF_CloseFont(m_pFont);
}

bool UI::loadFont(std::string path, int size)
{
	m_pFont = TTF_OpenFont(path.c_str(), size);
	if (!m_pFont)
	{
		printf("TTF_OpenFont Error: %s", TTF_GetError());
		return false;
	}
	return true;
}

void UI::drawText(std::string text, int x, int y, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_pFont, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_RenderCopy(m_pRenderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void UI::drawSprite(std::string textureID, int x, int y, int w, int h)
{
	SDL_Rect destRect;

	destRect.w = w;
	destRect.h = h;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(m_pRenderer, Renderer::getTexture(textureID), NULL, &destRect);
}