// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Obstacle.cpp 
// Description : Obstacle Implementation File		
// Author : Inman, Will; Frear Stace

#include "Obstacle.h"
#include "Math.h"
#include "BoxCollider.h"
#include "TextureLoader.h"
#include "VFX.h"

Obstacle::Obstacle(ObstacleProperties _properties)
{
	m_Properties = _properties;
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	m_Mesh.setScale(_properties.v2fScale);
	m_Mesh.setPosition(_properties.v2fStartPos);

	// Set box collider
	m_fColliderOffset = _properties.fBoxColliderOffsetY;
	m_BoxCollider = new BoxCollider(_properties.v2fBoxColliderSize, sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + m_fColliderOffset));
}

Obstacle::~Obstacle()
{
	switch (m_Properties.ObstacleType)
	{
		case OBSTACLETYPE::ROCK:
		{	
			// Play rock destruction VFX animation
			SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/rock_obstacle_explosion.png") };
			explosionProperties.v2fScale = { 2.0f, 2.0f };
			explosionProperties.v2fStartPos = m_Mesh.getPosition();
			explosionProperties.uNumberOfFrames = 4;
			explosionProperties.fAnimFrameInterval = 0.5f / 8;
			explosionProperties.v2fVelocity = { 0.0f, 160.0f };
			VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.25f);
			break;
		}
		case OBSTACLETYPE::HEDGE:
		{
			// Play log destruction VFX animation
			SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/hedge_obstacle_explosion.png") };
			explosionProperties.v2fScale = { 2.0f, 2.0f };
			explosionProperties.v2fStartPos = m_Mesh.getPosition();
			explosionProperties.uNumberOfFrames = 4;
			explosionProperties.fAnimFrameInterval = 0.5f / 8;
			explosionProperties.v2fVelocity = { 0.0f, 160.0f };
			VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.25f);
			break;
		}
		case OBSTACLETYPE::LOG:
		{
			// Play log destruction VFX animation
			SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/log_obstacle_explosion.png") };
			explosionProperties.v2fScale = { 2.0f, 2.0f };
			explosionProperties.v2fStartPos = m_Mesh.getPosition();
			explosionProperties.uNumberOfFrames = 4;
			explosionProperties.fAnimFrameInterval = 0.5f / 8;
			explosionProperties.v2fVelocity = { 0.0f, 160.0f };
			VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.25f);
			break;
		}
		default:
			break;
	}
}

void Obstacle::Update()
{
	Movement();

	// Update position of collider
	m_BoxCollider->SetPosition(sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + m_fColliderOffset));
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

BoxCollider* Obstacle::GetCollisionBox() const
{
	return m_BoxCollider;
}
