#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(ProjectileProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	m_Mesh.setScale(_properties.Scale);
	m_Mesh.setPosition(_properties.StartPos);
	//m_Mesh.setColor(sf::Color::Green);
	m_Properties.Damage = _properties.Damage;
	m_Properties.Friendly = _properties.Friendly;
	m_Properties.MoveSpeed = _properties.MoveSpeed;
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	if (m_Properties.Friendly == true)
	{
		m_Mesh.move({0.0f, -m_Properties.MoveSpeed * Statics::DeltaTime});
	}
	else if (m_Properties.Friendly == false)
	{
		m_Mesh.move({ 0.0f, m_Properties.MoveSpeed * Statics::DeltaTime });
	}
}

bool Projectile::CheckCollision(sf::Sprite _entitySprite)
{
	return m_Mesh.getGlobalBounds().intersects(_entitySprite.getGlobalBounds());
}

sf::Vector2f Projectile::GetPosition() const
{
	return m_Mesh.getPosition();
}

bool Projectile::IsFriendly() const
{
	return m_Properties.Friendly;
}

void Projectile::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
}
