// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : BoxCollider.h 
// Description : 
// Author : 
// Mail : 

#pragma once

#include "Statics.h"

class BoxCollider
{
public:
	BoxCollider(sf::Vector2f _size, sf::Vector2f _position);
	~BoxCollider();

	void UpdatePosition(sf::Vector2f _position);

	void DrawDebug(sf::RenderTarget& _target);

	bool CheckCollision(sf::RectangleShape* _otherCollider);

	bool bColliding = false;

private:
	sf::RectangleShape* m_Collider{};
	

public:
	// Getters
	sf::RectangleShape* GetCollider();

};

