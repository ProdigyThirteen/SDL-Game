#include "Player.h"
#include "SDL.h"
#include <string>
#include "InputHandler.h"

Player::Player(const AssetLoader* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
	
	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_RIGHT))
		m_velocity.setX(2);
	else if (m_velocity.getX() > 0)
		m_velocity.setX(0);
	
	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_LEFT))
		m_velocity.setX(-2);
	else if (m_velocity.getX() < 0)
		m_velocity.setX(0);

	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_UP))
		m_velocity.setY(-2);
	else if (m_velocity.getY() < 0)
		m_velocity.setY(0);

	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_DOWN))
		m_velocity.setY(2);
	else if (m_velocity.getY() > 0)
		m_velocity.setY(0);

	SDLGameObject::update();
}

void Player::cleanup()
{
}