// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : BoxCollider.h 
// Description : BoxCollider Header File
// Author : Frear, Stace

#pragma once
#include "Statics.h"

class BoxCollider
{
public:
	/// <summary>
	/// Box Collider Constructor
	/// </summary>
	/// <param name="_size"></param>
	/// <param name="_position"></param>
	BoxCollider(sf::Vector2f _size, sf::Vector2f _position);
	/// <summary>
	/// Box Collider Destructor
	/// </summary>
	~BoxCollider();

	/// <summary>
	/// Draws the box collider if debug mode is enabled
	/// </summary>
	/// <param name="_target"></param>
	void DrawDebug(sf::RenderTarget& _target);

	/// <summary>
	/// Checks for collision between the collider and a rectangle shape
	/// </summary>
	/// <param name="_someRectShape"></param>
	/// <returns></returns>
	bool CheckCollision(sf::RectangleShape& _someRectShape);
	/// <summary>
	/// Checks for collision between the collider and the specified floatRect
	/// </summary>
	/// <param name="_aFloatRect"></param>
	/// <returns></returns>
	bool CheckCollision(sf::FloatRect _aFloatRect);
	/// <summary>
	/// Checks for collision between the collider and another collider
	/// </summary>
	/// <param name="_otherCollider"></param>
	/// <returns></returns>
	bool CheckCollision(BoxCollider& _otherCollider);

	bool bColliding{ false };

private:
	sf::RectangleShape m_Collider{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	sf::RectangleShape& GetCollider();

	void SetPosition(sf::Vector2f _position);
};

