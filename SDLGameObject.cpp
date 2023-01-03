#include "SDLGameObject.h"
#include "Vec2.h"
#include "Collider.h"
#include "game.h"

SDLGameObject::SDLGameObject(const AssetLoader* pParams, const bool isStaticObject, Collider* pCollider)
	: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_pCollider(pCollider), m_bIsStaticObject(isStaticObject)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
}

SDLGameObject::SDLGameObject(const AssetLoader* pParams, const bool isStaticObject)
	: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_pCollider(nullptr), m_bIsStaticObject(isStaticObject)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
}

SDLGameObject::SDLGameObject(const bool isStaticObject) // TODO: Refactor game to add more game object variants
	: GameObject(nullptr), m_position(0, 0), m_velocity(0, 0), m_pCollider(nullptr), m_bIsStaticObject(isStaticObject)
{
	m_width = 0;
	m_height = 0;
	m_textureID = "";
	m_currentRow = 1;
}

SDLGameObject::~SDLGameObject()
{
	if(m_pCollider)
		delete m_pCollider;

	m_pCollider = nullptr;
}

void SDLGameObject::update()
{
	if (getIsStatic())
		return;

	// Handle movement, adjusted for delta time
	m_velocity += m_acceleration;
	m_position += m_velocity * game::Instance()->getDeltaTime();
	m_acceleration = Vec2(0,0);
	
	// Handle friction
	m_velocity.x -= m_friction * m_velocity.x * game::Instance()->getDeltaTime();
	m_velocity.y -= m_friction * m_velocity.y * game::Instance()->getDeltaTime();
}

void SDLGameObject::checkCollisions()
{
	// Skip if no collider
	if (!m_pCollider)
		return;

	// Skip if object is static
	if (m_bIsStaticObject)
		return;

	//Check for collision
	for (auto& other : game::Instance()->getGameObjects())
	{
		// Skip if other object has no collider
		if (&other->getCollider() == nullptr)
			continue;
		
		// Skip if checking against self
		if (shared_from_this() == other)
			continue;

		if (m_pCollider->CheckCollision(other->getCollider()))
		{
			printf("Collision detected between %s and %s\n", getCollider().GetTag().c_str(), other->getCollider().GetTag().c_str());
			m_bIsColliding = true;
			onCollision(other);
		}
	}
}

void SDLGameObject::onCollision(std::shared_ptr<SDLGameObject> pOther)
{
}