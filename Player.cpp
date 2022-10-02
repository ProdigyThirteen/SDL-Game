#include "Player.h"
#include "SDL.h"
#include <string>

Player::Player(const AssetLoader* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
}

void Player::clean()
{
}