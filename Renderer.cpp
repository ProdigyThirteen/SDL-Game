#include "Renderer.h"
#include "SDL_Image.h"
#include "game.h"

//textureManager* textureManager::s_pInstance = 0;

std::map<std::string, textureData*> Renderer::m_textureMap;
int drawCount = 0;

bool Renderer::loadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer, int framesOfAnimation)
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
		m_textureMap[id] = new textureData{ pTexture, framesOfAnimation };
		SDL_FreeSurface(pTempSurface);
		
		return true;
	}

	return false;
}

void Renderer::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	// Skip drawing if outside screen bounds, offset by camera position
	if (x + width < game::Instance()->getCameraPos().x || 
		x > game::Instance()->getCameraPos().x + SCREEN_WIDTH || 
		y + height < game::Instance()->getCameraPos().y || 
		y > game::Instance()->getCameraPos().y + SCREEN_HEIGHT)
		return;	

	Vec2 CameraPos = game::Instance()->getCameraPos();

	drawCount++;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - CameraPos.x;
	destRect.y = y - CameraPos.y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void Renderer::drawRot(std::string id, int x, int y, int width, int height, float rotation, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x - game::Instance()->getCameraPos().x;
	destRect.y = y - game::Instance()->getCameraPos().y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, rotation, 0, flip);
}

void Renderer::drawFrame(std::string id, int x, int y, int width, int height, int currentCol, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
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

	SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, 0, 0, flip);
}

void Renderer::drawFrameRot(std::string id, int x, int y, int width, int height, float rotation, int currentCol, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
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

	SDL_RenderCopyEx(pRenderer, m_textureMap[id]->texture, &srcRect, &destRect, rotation, 0, flip);
}

void drawTilemap(SDL_Renderer* pRenderer)
{
	
}

int Renderer::getDrawCount()
{
	int temp = drawCount;
	drawCount = 0;
	return temp;
}

SDL_Texture* Renderer::getTexture(std::string id)
{
	return m_textureMap.at(id)->texture;
}