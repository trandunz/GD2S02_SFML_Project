#pragma once
#include "Statics.h"
#include "Math.h"

class Obstacle : public sf::Drawable
{
public:
	Obstacle(ObstacleProperties _properties);
	~Obstacle();

	void Update();

	sf::Sprite GetSprite() const;
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void Movement();

	ObstacleProperties m_Properties;
	sf::Vector2f m_v2fVelocity{};
	sf::Sprite m_Mesh{};
};

