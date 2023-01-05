#include <string>
#include <memory>
#include "SDL.h"
#include "Config.h"
#include "Player.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "UI.h"
#include "Sounds.h"
#include "Game.h"
#include "CircleCollider.h"
#include "Bullet.h"

Player::Player(const AssetLoader* pParams) 
	: SDLGameObject(pParams, false, new CircleCollider(m_position, 8, 24, 24, false, "player"))
{
	m_lastSafeLocation = m_position;
	m_friction = 10;
	m_maxSpeed = 60;
	m_speed = 50;
}

void Player::setRotation()
{
	Vec2* vec = inputHandler::getMousePosition();
	float x = vec->x - (m_position.x + m_width / 2) + game::Instance()->getCameraPos().x;
	float y = vec->y - (m_position.y + m_height / 2) + game::Instance()->getCameraPos().y;
	m_rotation = (float)(atan2(y, x) * 180 / M_PI);
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
	m_pCollider->Debug();
	switch (m_playerState)
	{
	case IDLE:
		Renderer::drawRot(m_textureID, (int)m_position.x, (int)m_position.y, m_width, m_height, m_rotation);
		break;

	case SHOOTING:
		Renderer::drawFrameRot(m_textureID, (int)m_position.x , (int)m_position.y, m_width, m_height, m_rotation, m_currentRow);
		break;
	}

	// Draw ammo
	UI::drawText(std::to_string(m_ammo), 10, 10, { 255, 255, 255, 255 });
}

void Player::update()
{
	setRotation();
	setTexture();

	// Update counter
	m_fireRateCounter++;
		
	// Handle Movement
	m_lastSafeLocation = m_position;
	
	if (!m_bIsColliding)
	{		
		if (inputHandler::isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler::isKeyDown(SDL_SCANCODE_D))
			m_acceleration.x += m_speed;
		/*else if (m_velocity.x > 0)
			m_velocity.x = 0;*/
	
		if (inputHandler::isKeyDown(SDL_SCANCODE_LEFT) || inputHandler::isKeyDown(SDL_SCANCODE_A))
			m_acceleration.x += -m_speed;
		//else if (m_velocity.x < 0)
		//	m_velocity.x = 0;

		if (inputHandler::isKeyDown(SDL_SCANCODE_UP) || inputHandler::isKeyDown(SDL_SCANCODE_W))
			m_acceleration.y += -m_speed;
		//else if (m_velocity.y < 0)
		//	m_velocity.y = 0;

		if (inputHandler::isKeyDown(SDL_SCANCODE_DOWN) || inputHandler::isKeyDown(SDL_SCANCODE_S))
			m_acceleration.y += m_speed;
		//else if (m_velocity.y > 0)
		//	m_velocity.y = 0;
	}

	// Handle shooting
	if (inputHandler::getMouseButtonState(LEFT) && m_ammo > 0)
	{
		m_playerState = SHOOTING;

		// Check if the player can shoot
		if (m_fireRateCounter >= m_fireRate && m_ammo > 0)
		{
			m_fireRateCounter = 0;
			
			// Calculate bullet direction
			Vec2* vec = inputHandler::getMousePosition();
			float x = vec->x - (m_position.x + m_width / 2) + game::Instance()->getCameraPos().x;
			float y = vec->y - (m_position.y + m_height / 2) + game::Instance()->getCameraPos().y;
			float angle = (float)(atan2(y, x) * 180 / M_PI);
			Vec2 direction = Vec2(cos(angle * M_PI / 180), sin(angle * M_PI / 180));
			direction.Normalize();

			// Calculate bullet offset
			Vec2 offset = Vec2(cos(angle * M_PI / 180), sin(angle * M_PI / 180));
			offset *= m_bulletOffset;

			// Calculate the bullet position
			Vec2 bulletPosition = Vec2(m_position.x + (m_width / 2), m_position.y + (m_height / 2));
			bulletPosition += offset;
			
			// Create a bullet
			std::shared_ptr<SDLGameObject> temp = std::make_shared<Bullet>(new AssetLoader(bulletPosition.x + direction.x, bulletPosition.y + direction.y, 8, 8, "bullet"));

			// Set the bullet velocity
			temp->setVelocity(direction * m_bulletSpeed);

			// Add the bullet to the game object vector
			game::Instance()->addObject(temp);

			// Play the shooting sound
			Sounds::playSound("gunshot");

			// Subtract ammo
			m_ammo--;
		}

		// Reset the animation if out of ammo
		if (m_ammo <= 0)
		{
			m_playerState = IDLE;
			m_currentRow = 0;
		}
		
	}
	if (!inputHandler::getMouseButtonState(LEFT))
	{
		m_playerState = IDLE;
	}
	
	// Update parent class and collider
	SDLGameObject::update();
	m_pCollider->Update();

	// Update the camera
	game::Instance()->setCameraPos(Vec2(m_position.x + m_width / 2 - SCREEN_WIDTH / 2, m_position.y + m_height / 2 - SCREEN_HEIGHT / 2));
}

void Player::cleanup()
{
}

void Player::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
	m_position = m_lastSafeLocation;
	m_pCollider->Update();
	m_bIsColliding = false;
}