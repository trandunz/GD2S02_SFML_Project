#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::Vector2f _size, sf::Vector2f _position)
{
	// Set sfml rectangle shape size, position and origin
	m_Collider = new sf::RectangleShape(_size);
	m_Collider->setPosition(_position);
	m_Collider->setOrigin(m_Collider->getSize().x / 2, m_Collider->getSize().y / 2);


	// Set visual of the collider to be a colored outline, that
	// will only show in debug mode
	m_Collider->setFillColor(sf::Color::Transparent);
	m_Collider->setOutlineThickness(1.0f);
	m_Collider->setOutlineColor(sf::Color::Magenta);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::UpdatePosition(sf::Vector2f _position)
{
	m_Collider->setPosition(_position);
}

void BoxCollider::DrawDebug(sf::RenderTarget& _target)
{
	if (Statics::bDebugMode)
		_target.draw(*m_Collider);
}

bool BoxCollider::CheckCollision(sf::RectangleShape* _otherCollider)
{
	return m_Collider->getGlobalBounds().intersects(_otherCollider->getGlobalBounds());
}

bool BoxCollider::CheckCollision(sf::FloatRect _otherCollider)
{
	if (m_Collider)
	{
		return m_Collider->getGlobalBounds().intersects(_otherCollider);
	}
	else
	{
		return false;
	}
}

bool BoxCollider::CheckCollision(BoxCollider& _otherCollider)
{
	if (m_Collider)
	{
		return m_Collider->getGlobalBounds().intersects(_otherCollider.GetCollider()->getGlobalBounds());
	}
	else
	{
		return false;
	}
}

sf::RectangleShape* BoxCollider::GetCollider()
{
	return m_Collider;
}
