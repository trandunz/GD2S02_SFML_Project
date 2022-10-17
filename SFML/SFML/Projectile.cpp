// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Projectile.cpp 
// Description : Projectile Implementation File		
// Author : Inman, Will

#include "Projectile.h"
#include "Player.h"
#include "BoxCollider.h"
#include "TextureLoader.h"
#include "VFX.h"

Projectile::Projectile(ProjectileProperties _properties)
{
	m_Properties = _properties;

	AnimStateProperties animProperties;
	animProperties.StateTexture = _properties.Texture;
	animProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animProperties.fFrameInterval = 0.1f;
	animProperties.bLoops = true;
	animProperties.v2fScale = _properties.v2fScale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");
	m_AnimatedSprite.SetPosition(_properties.v2fStartPos);
	m_AnimatedSprite.StartState("Moving");

	sf::Vector2f colliderSize{};
	switch (m_Properties.eProjectileType)
	{
		case PROJECTILETYPE::BASIC:
		{
			colliderSize = { 24.0f, 48.0f };
			
			if (m_Properties.bFriendly == false)
			{
				m_AnimatedSprite.SetRotation(180.0f);
			}
			
			break;
		}
		case PROJECTILETYPE::SECONDARY:
		{
			//colliderSize.x *= _properties.v2fScale.x;
			//colliderSize.y *= _properties.v2fScale.y;
			colliderSize = {64.0f,64.0f };
			break;
		}
		case PROJECTILETYPE::ARROW:
		{
			colliderSize = { 8.0f, 32.0f };
			break;
		}
		default:
			break;
	}
	
	m_BoxCollider = new BoxCollider(colliderSize, _properties.v2fStartPos);
}

Projectile::~Projectile()
{
	if (m_BoxCollider)
	{
		delete m_BoxCollider;
		m_BoxCollider = nullptr;
	}
}

void Projectile::Update()
{
	if (m_Properties.bFriendly == true)
	{
		m_AnimatedSprite.GetSprite().move({0.0f, -m_Properties.fMoveSpeed * Statics::fDeltaTime});
	}
	else if (m_Properties.bFriendly == false)
	{
		m_AnimatedSprite.GetSprite().move({ 0.0f, m_Properties.fMoveSpeed * Statics::fDeltaTime });
	}

	m_AnimatedSprite.Update();

	// Update position of collider
	if (m_BoxCollider)
		m_BoxCollider->SetPosition(m_AnimatedSprite.GetPosition());
}

bool Projectile::CheckCollision(BoxCollider& _otherCollider)
{
	if (m_BoxCollider)
	{
		return m_BoxCollider->CheckCollision(_otherCollider);
	}
	else
	{
		return false;
	}
}

BoxCollider* Projectile::GetCollider()
{
	return m_BoxCollider;
}

sf::Vector2f Projectile::GetPosition() const
{
	return m_AnimatedSprite.GetPosition();//m_Mesh.getPosition();
}

unsigned Projectile::GetDamagedDealt() const
{
	return m_Properties.uDamage;
}

ELEMENTTYPE Projectile::GetElement() const
{
	return m_Properties.eElement;
}

PROJECTILETYPE Projectile::GetProjectileType() const
{
	return m_Properties.eProjectileType;
}

bool Projectile::IsFriendly() const
{
	return m_Properties.bFriendly;
}

bool Projectile::IsDestroyedOnCollision() const
{
	return m_Properties.bDestroyOnCollision;
}

bool Projectile::DoesApplyElementToTarget() const
{
	return m_Properties.bApplyElementToTarget;
}

void Projectile::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_AnimatedSprite);

	// Draw box collider if debug mode turned on
	if (m_BoxCollider)
		m_BoxCollider->DrawDebug(_target);
}
