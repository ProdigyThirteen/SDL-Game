#include "Renderer.h"
#include "SDL_Image.h"
#include "game.h"
#include "Utils.h"

std::map<std::string, textureData*> Renderer::m_textureMap;
SDL_Renderer* Renderer::m_pRenderer;

bool Renderer::loadTexture(std::string fileName, std::string id, int framesOfAnimation)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
	{
		Utils::SetConsoleColour(Utils::ConsoleColour::RED);
		printf("IMG_Load Error: %s", IMG_GetError());
		Utils::SetConsoleColour(Utils::ConsoleColour::WHITE);
		return false;
	}

	printf("%s loaded!\n", fileName.c_str());

	if (SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface))
	{
		m_textureMap[id] = new textureData{ pTexture, framesOfAnimation };
		SDL_FreeSurface(pTempSurface);
		
		return true;
	}

	return false;
}

void Renderer::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	// Skip drawing if outside screen bounds, offset by camera position
	if (x + width < game::Instance()->getCameraPos().x || 
		x > game::Instance()->getCameraPos().x + SCREEN_WIDTH || 
		y + height < game::Instance()->getCameraPos().y || 
		y > game::Instance()->getCameraPos().y + SCREEN_HEIGHT)
		return;	

	Vec2 CameraPos = game::Instance()->getCameraPos();

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - CameraPos.x;
	destRect.y = y - CameraPos.y;

	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void Renderer::drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - game::Instance()->getCameraPos().x;
	destRect.y = y - game::Instance()->getCameraPos().y;

	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, rotation, 0, flip);
}

void Renderer::drawFrame(std::string id, int x, int y, int width, int height, int currentCol, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	m_textureMap[id]->currentFrame = int(((SDL_GetTicks() / 100) % m_textureMap[id]->frames));
	
	srcRect.x = width * (currentCol - 1);
	srcRect.y = height * (m_textureMap[id]->currentFrame);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - game::Instance()->getCameraPos().x;
	destRect.y = y - game::Instance()->getCameraPos().y;

	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void Renderer::drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol,  SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	m_textureMap[id]->currentFrame = int(((SDL_GetTicks() / 100) % m_textureMap[id]->frames));

	srcRect.x = width * (currentCol - 1);
	srcRect.y = height * (m_textureMap[id]->currentFrame);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - game::Instance()->getCameraPos().x;
	destRect.y = y - game::Instance()->getCameraPos().y;

	SDL_RenderCopyEx(m_pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, rotation, 0, flip);
}

SDL_Texture* Renderer::getTexture(std::string id)
{
	return m_textureMap.at(id)->texture;
}

bool Renderer::init(SDL_Window* pWindow)
{
	m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_pRenderer)
	{
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Renderer::cleanup()
{
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second->texture);
		delete it->second;
	}

	SDL_DestroyRenderer(m_pRenderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return m_pRenderer;
}

void Renderer::clear()
{
	SDL_RenderClear(m_pRenderer);
}

void Renderer::present()
{
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::setDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}