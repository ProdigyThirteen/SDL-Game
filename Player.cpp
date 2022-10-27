#include "Player.h"
#include "SDL.h"
#include <string>
#include "InputHandler.h"

#include "textureManager.h"
#include "Game.h"

Player::Player(const AssetLoader* pParams) : SDLGameObject(pParams) {}

void Player::setRotation()
{
	Vec2* vec = inputHandler::getMousePosition();
	float x = vec->getX() - (m_position.getX() + m_width / 2);
	float y = vec->getY() - (m_position.getY() + m_height / 2);
	m_rotation = atan2(y, x) * 180 / 3.14159265;
}

void Player::setTexture()
{
	switch (m_playerState)
	{
	case IDLE:
		m_textureID = "playerIdle";
		break;
		
	case SHOOTING:
		m_textureID = "playerShooting";
		break;
	}
}

void Player::draw()
{
	switch (m_playerState)
	{
	case IDLE:
		textureManager::drawRot(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_rotation, game::Get()->getRenderer());
		break;

	case SHOOTING:
		textureManager::drawFrameRot(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_rotation, m_currentRow, m_currentFrame, game::Get()->getRenderer());
		break;
	}
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_framesOfAnimation));

	setRotation();
	setTexture();
	
	//example iskeydown input
	if (inputHandler::isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler::isKeyDown(SDL_SCANCODE_D))
		m_velocity.setX(2);
	else if (m_velocity.getX() > 0)
		m_velocity.setX(0);
	
	if (inputHandler::isKeyDown(SDL_SCANCODE_LEFT) || inputHandler::isKeyDown(SDL_SCANCODE_A))
		m_velocity.setX(-2);
	else if (m_velocity.getX() < 0)
		m_velocity.setX(0);

	if (inputHandler::isKeyDown(SDL_SCANCODE_UP) || inputHandler::isKeyDown(SDL_SCANCODE_W))
		m_velocity.setY(-2);
	else if (m_velocity.getY() < 0)
		m_velocity.setY(0);

	if (inputHandler::isKeyDown(SDL_SCANCODE_DOWN) || inputHandler::isKeyDown(SDL_SCANCODE_S))
		m_velocity.setY(2);
	else if (m_velocity.getY() > 0)
		m_velocity.setY(0);

	if (inputHandler::getMouseButtonState(LEFT))
	{
		m_playerState = SHOOTING;
	}
	if (!inputHandler::getMouseButtonState(LEFT))
	{
		m_playerState = IDLE;
	}

	//example keydown/keyup input
	if (inputHandler::onKeyDown(SDL_SCANCODE_G))
		m_velocity.setX(10);

	if (inputHandler::onKeyUp(SDL_SCANCODE_F))
		m_velocity.setY(100);


	SDLGameObject::update();
}

void Player::cleanup()
{
}