#include "TextureManager.h"
#include "SDL_Image.h"

//textureManager* textureManager::s_pInstance = 0;

std::map<std::string, SDL_Texture*> textureManager::m_textureMap;

bool textureManager::loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (!pTempSurface)
	{
		printf("IMG_Load Error: %s", IMG_GetError());
		return false;
	}

	printf("%s loaded!\n", fileName.c_str());

	if (SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface))
	{
		m_textureMap[id] = pTexture;
		SDL_FreeSurface(pTempSurface);
		return true;
	}

	return false;
}

void textureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void textureManager::drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, rotation, 0, flip);
}

void textureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentCol, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = width * (currentCol - 1);
	srcRect.y = height * (currentFrame);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void textureManager::drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * (currentCol - 1);
	srcRect.y = height * (currentFrame);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, rotation, 0, flip);
}