#include "Character.h"
#include "Bullet.h"
#include "Game.h"
#include "Sounds.h"

Character::Character(const AssetLoader* pParams, bool isEnemy, Collider* pCollider, const std::string tag)
	: SDLGameObject(pParams, false, pCollider, tag), m_isEnemy(isEnemy)
{
}

Character::~Character()
{
}

void Character::Shoot(Vec2 target, int bulletSpeed, bool canDamagePlayer)
{
	// Calculate bullet direction
	Vec2 vec = target;
	float x = vec.x - (m_position.x + m_width / 2);
	float y = vec.y - (m_position.y + m_height / 2);
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
	std::shared_ptr<SDLGameObject> temp = std::make_shared<Bullet>(new AssetLoader(bulletPosition.x + direction.x, bulletPosition.y + direction.y, 8, 8, "bullet"), canDamagePlayer);

	// Set the bullet velocity
	temp->setVelocity(direction * bulletSpeed);

	// Add the bullet to the game object vector
	game::Instance()->addObject(temp);

	// Play the shooting sound
	Sounds::playSound("gunshot");
}