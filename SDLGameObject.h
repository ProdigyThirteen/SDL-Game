#pragma once

#include <memory>
#include <string>
#include "GameObject.h"
#include "AssetLoader.h"
#include "Vec2.h"
#include "Collider.h"

class SDLGameObject : public GameObject, public std::enable_shared_from_this<SDLGameObject>
{
protected:
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;
	float m_friction = 0;
	int m_maxSpeed = 0;
	int m_speed = 0;
	
	int m_width;
	int m_height;
	int m_currentRow;
	float m_rotation;
	
	std::string m_textureID;
	const std::string m_tag;

	Collider* m_pCollider;
	bool m_bIsColliding = false;
	const bool m_bIsStaticObject;

public:
	SDLGameObject(const AssetLoader* pParams, const bool isStaticObject, Collider* pCollider, const std::string tag);
	SDLGameObject(const AssetLoader* pParams, const bool isStaticObject, const std::string tag);
	SDLGameObject(const bool isStaticObject, const std::string tag);
	~SDLGameObject();
	
	virtual void draw() = 0;
	virtual void update();
	virtual void cleanup() = 0;
	virtual void onCollision(std::shared_ptr<SDLGameObject> pOther);
	void checkCollisions();

	void setVelocity(Vec2 velocity) { m_velocity = velocity; }

	Collider& getCollider() { return *m_pCollider; }
	bool getIsStatic() { return m_bIsStaticObject; }
	Vec2 getPosition() { return m_position; }
	std::string getTag() { return m_tag; }
};