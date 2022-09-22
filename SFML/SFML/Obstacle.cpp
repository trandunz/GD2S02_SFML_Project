// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Obstacle.cpp 
// Description : Obstacle Implementation File		
// Author : Inman, Will

#include "Obstacle.h"
#include "Math.h"
#include "BoxCollider.h"

Obstacle::Obstacle(ObstacleProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	m_Mesh.setScale(_properties.v2fScale);
	m_Mesh.setPosition(_properties.v2fStartPos);

	// Set box collider
	fColliderOffset = _properties.fBoxColliderOffsetY;
	m_BoxCollider = new BoxCollider(_properties.BoxColliderSize, sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + fColliderOffset));
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	Movement();

	// Update position of collider
	m_BoxCollider->UpdatePosition(sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + fColliderOffset));
}

sf::Sprite Obstacle::GetSprite() const
{
	return m_Mesh;
}

void Obstacle::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);

	// Draw box collider if debug mode turned on
	m_BoxCollider->DrawDebug(_target);
}

void Obstacle::Movement()
{
	m_v2fVelocity = { 0,1 };
	m_Mesh.move(m_v2fVelocity * Statics::fBackgroundScrollSpeed * Statics::fDeltaTime);
}

BoxCollider* Obstacle::GetCollisionBox()
{
	return m_BoxCollider;
}
