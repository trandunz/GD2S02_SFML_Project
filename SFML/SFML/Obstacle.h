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
	/// <summary>
	/// Construct an obstacle with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	Obstacle(ObstacleProperties _properties);
	/// <summary>
	/// Obstacle destructor
	/// </summary>
	~Obstacle();

	/// <summary>
	/// Update the obstacle
	/// </summary>
	void Update();

	bool bDestroy{ false };
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Handles movement for the obstacle 
	/// </summary>
	void Movement();

	ObstacleProperties m_Properties{};
	sf::Vector2f m_v2fVelocity{};
	sf::Sprite m_Mesh{};

	BoxCollider* m_BoxCollider{nullptr};
	float m_fColliderOffset{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	sf::Sprite GetSprite() const;

	BoxCollider* GetCollisionBox();
};

