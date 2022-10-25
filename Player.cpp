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
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_framesOfAnimation));
	
	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler::Get()->isKeyDown(SDL_SCANCODE_D))
		m_velocity.setX(2);
	else if (m_velocity.getX() > 0)
		m_velocity.setX(0);
	
	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_LEFT) || inputHandler::Get()->isKeyDown(SDL_SCANCODE_A))
		m_velocity.setX(-2);
	else if (m_velocity.getX() < 0)
		m_velocity.setX(0);

	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_UP) || inputHandler::Get()->isKeyDown(SDL_SCANCODE_W))
		m_velocity.setY(-2);
	else if (m_velocity.getY() < 0)
		m_velocity.setY(0);

	if (inputHandler::Get()->isKeyDown(SDL_SCANCODE_DOWN) || inputHandler::Get()->isKeyDown(SDL_SCANCODE_S))
		m_velocity.setY(2);
	else if (m_velocity.getY() > 0)
		m_velocity.setY(0);

	if (inputHandler::Get()->onKeyDown(SDL_SCANCODE_G))
		m_velocity.setX(10);


	SDLGameObject::update();
}

void Player::cleanup()
{
}