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
	: Character(pParams, false, new CircleCollider(m_position, 8, 24, 24, false, "player"), "Player")
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
	//m_pCollider->Debug();
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
	UI::drawSprite("ui_bullet", 10, 12, 32, 32);
	UI::drawText(std::to_string(m_ammo), 40, 10, { 255, 255, 255, 255 });

	// Draw health
	UI::drawSprite("ui_heart", 10, 52, 32, 32);
	UI::drawText(std::to_string(m_health), 40, 50, { 255, 255, 255, 255 });
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
	
		if (inputHandler::isKeyDown(SDL_SCANCODE_LEFT) || inputHandler::isKeyDown(SDL_SCANCODE_A))
			m_acceleration.x += -m_speed;

		if (inputHandler::isKeyDown(SDL_SCANCODE_UP) || inputHandler::isKeyDown(SDL_SCANCODE_W))
			m_acceleration.y += -m_speed;

		if (inputHandler::isKeyDown(SDL_SCANCODE_DOWN) || inputHandler::isKeyDown(SDL_SCANCODE_S))
			m_acceleration.y += m_speed;
	}

	// Handle shooting
	if (inputHandler::getMouseButtonState(LEFT) && m_ammo > 0)
	{
		m_playerState = SHOOTING;

		// Check if the player can shoot
		if (m_fireRateCounter >= m_fireRate && m_ammo > 0)
		{
			m_fireRateCounter = 0;

			Vec2 target = *inputHandler::getMousePosition();
			target.x += game::Instance()->getCameraPos().x;
			target.y += game::Instance()->getCameraPos().y;

			Shoot(target, 600, false);
			m_ammo--;
		}

		// Reset the animation if out of ammo
		if (m_ammo <= 0)
		{
			m_playerState = IDLE;
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
	// Check if the player is colliding with a wall
	if (pOther->getCollider().GetTag() == "Wall" || pOther->getCollider().GetTag() == "Crate")
	{
		m_position = m_lastSafeLocation;
	}

	// Check if the player is colliding with an AmmoDrop
	else if (pOther->getCollider().GetTag() == "AmmoDrop")
	{
		// Add ammo, respecting max ammo
		if (m_ammo + 10 > m_maxAmmo)
			m_ammo = m_maxAmmo;
		else
			m_ammo += 10;

		game::Instance()->removeObject(pOther);
	}

	// Check if the player is colliding with an Enemy
	else if (pOther->getCollider().GetTag() == "Enemy")
	{
		// Take damage
		m_health--;
		
		// Knock player back relative to enemy position
		Vec2 enemyPos = pOther->getPosition();
		Vec2 playerPos = m_position;
		Vec2 knockback = enemyPos - playerPos;
		knockback.Normalize();
		m_acceleration.x = knockback.x * -150;
		m_acceleration.y = knockback.y * -150;
	}

	else if (pOther->getCollider().GetTag() == "Bullet")
	{
		auto bullet = std::dynamic_pointer_cast<Bullet>(pOther);
		if (bullet->CanDamagePlayer())
		{
			m_health--;
			bullet->SetCanDamagePlayer(false);
		}
	}

	else if (pOther->getTag() == "LevelExit" && game::Instance()->getEnemiesRemaining() == 0)
	{
		game::Instance()->gameOver();
	}
	
	m_pCollider->Update();
	m_bIsColliding = false;
}