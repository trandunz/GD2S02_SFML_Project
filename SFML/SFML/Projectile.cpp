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

Projectile::Projectile(ProjectileProperties _properties)
{
	AnimStateProperties animProperties;
	animProperties.StateTexture = _properties.Texture;
	animProperties.NumberOfFrames = _properties.uNumberOfFrames;
	animProperties.FrameInterval = 0.1f;
	animProperties.Loops = true;
	animProperties.Scale = _properties.Scale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");

	//m_Mesh.setTexture(*_properties.Texture, true);
	//SetOriginCenter(m_Mesh);
	//m_Mesh.setScale(_properties.Scale);
	//m_Mesh = m_AnimatedSprite.GetSprite();
	m_AnimatedSprite.SetPosition(_properties.StartPos);
	//m_AnimatedSprite.GetSprite().setColor(sf::Color::Green);
	m_Properties.uDamage = _properties.uDamage;
	m_Properties.bFriendly = _properties.bFriendly;
	m_Properties.fMoveSpeed = _properties.fMoveSpeed;

	m_AnimatedSprite.StartState("Moving");

	sf::Vector2f colliderSize{ 32,32 };
	colliderSize.x *= _properties.Scale.x;
	colliderSize.y *= _properties.Scale.y;
	m_BoxCollider = new BoxCollider(colliderSize, _properties.StartPos);
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
		m_BoxCollider->UpdatePosition(m_AnimatedSprite.GetPosition());
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

sf::Vector2f Projectile::GetPosition() const
{
	return m_AnimatedSprite.GetPosition();//m_Mesh.getPosition();
}

bool Projectile::IsFriendly() const
{
	return m_Properties.bFriendly;
}

void Projectile::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_AnimatedSprite);

	// Draw box collider if debug mode turned on
	if (m_BoxCollider)
		m_BoxCollider->DrawDebug(_target);
}
