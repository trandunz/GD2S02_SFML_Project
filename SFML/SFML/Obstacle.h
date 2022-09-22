// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Obstacle.h 
// Description : Obstacle Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class BoxCollider;
class Obstacle : public sf::Drawable
{
public:
	Obstacle(ObstacleProperties _properties);
	~Obstacle();

	void Update();

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void Movement();

	ObstacleProperties m_Properties{};
	sf::Vector2f m_v2fVelocity{};
	sf::Sprite m_Mesh{};

	BoxCollider* m_BoxCollider;
	float fColliderOffset;

public:
	// Getters
	sf::Sprite GetSprite() const;
	BoxCollider* GetCollisionBox();
};

