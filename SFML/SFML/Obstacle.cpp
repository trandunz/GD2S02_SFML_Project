#include "Obstacle.h"

Obstacle::Obstacle(ObstacleProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	m_Mesh.setScale(_properties.Scale);
	m_Mesh.setPosition(_properties.StartPos);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	Movement();
}

sf::Sprite Obstacle::GetSprite() const
{
	return m_Mesh;
}

void Obstacle::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
}

void Obstacle::Movement()
{
	m_v2fVelocity = { 0,1 };
	m_Mesh.move(m_v2fVelocity * m_Properties.MoveSpeed * Statics::DeltaTime);
}
