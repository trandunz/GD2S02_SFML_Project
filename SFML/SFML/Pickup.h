// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Pickup.h 
// Description : Pickup Header File
// Author : Inman, Will

#pragma once
#include "Animator.h"

class Player;
class BoxCollider;
class Pickup : public sf::Drawable
{
public:
	/// <summary>
	/// create a pickup with the given properties
	/// </summary>
	/// <param name="_properties"></param>
	Pickup(PickupProperties _properties);
	/// <summary>
	/// Pickup Destructor
	/// </summary>
	virtual ~Pickup();

	/// <summary>
	/// Pickup update
	/// </summary>
	void Update();

	/// <summary>
	/// Checks if the specified player is colliding with the pickup and returns bool.
	/// </summary>
	/// <param name="_player"></param>
	/// <returns></returns>
	bool CheckForPickup(Player& _player);

	bool bDestroy{ false };
protected:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Move the pickup by the specified amount
	/// </summary>
	/// <param name="_amount"></param>
	void Move(sf::Vector2f _amount);
	/// <summary>
	/// Sets the sprite texture depending on the pickup type
	/// </summary>
	/// <param name="_animProperties"></param>
	void SetAnimStateTextureBasedOnType(AnimStateProperties& _animProperties);
	/// <summary>
	/// Gives the specified player thee effct corresponding too the pickup type
	/// </summary>
	/// <param name="_player"></param>
	void GivePlayerPickupEffect(Player& _player);

	PickupProperties m_Properties{};
	Animator m_Animator{};
	BoxCollider* m_BoxCollider{nullptr};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	void SetPosition(sf::Vector2f _newPosition);
	sf::Vector2f GetPosition();
};

