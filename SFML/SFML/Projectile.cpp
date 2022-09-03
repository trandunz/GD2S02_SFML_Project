#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(ProjectileProperties _properties)
{
	AnimStateProperties animProperties;
	animProperties.StateTexture = _properties.Texture;
	animProperties.NumberOfFrames = 3;
	animProperties.FrameInterval = 0.1f;
	animProperties.Loops = true;
	animProperties.Scale = _properties.Scale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");

	//m_Mesh.setTexture(*_properties.Texture, true);
	//SetOriginCenter(m_Mesh);
	//m_Mesh.setScale(_properties.Scale);
	//m_Mesh = m_AnimatedSprite.GetSprite();
	m_AnimatedSprite.GetSprite().setPosition(_properties.StartPos);
	//m_AnimatedSprite.GetSprite().setColor(sf::Color::Green);
	m_Properties.uDamage = _properties.uDamage;
	m_Properties.bFriendly = _properties.bFriendly;
	m_Properties.fMoveSpeed = _properties.fMoveSpeed;

	m_AnimatedSprite.StartState("Moving");
}

Projectile::~Projectile()
{
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
}

bool Projectile::CheckCollision(sf::Sprite _entitySprite)
{
	return m_AnimatedSprite.GetSprite().getGlobalBounds().intersects(_entitySprite.getGlobalBounds());
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
}
