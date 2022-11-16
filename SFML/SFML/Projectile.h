// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Projectile.h 
// Description : Projectile Header File
// Author : Inman, Will

#pragma once
#include "Animator.h"

class BoxCollider;
class Projectile : public sf::Drawable
{
public:
	/// <summary>
	/// Create a projectile with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	Projectile(ProjectileProperties _properties);
	/// <summary>
	/// Projectile destructor
	/// </summary>
	~Projectile();

	/// <summary>
	/// Projectile update
	/// </summary>
	void Update();

	/// <summary>
	/// Bool to indicate if collides with player
	/// </summary>
	/// <returns></returns>
	bool IsFriendly() const;

	/// <summary>
	/// Check the collision between the projectile and the specified collider. Returns bools.
	/// </summary>
	/// <param name="_otherCollider"></param>
	/// <returns></returns>
	bool CheckCollision(BoxCollider& _otherCollider);

	bool bDestroy{ false };
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	ProjectileProperties m_Properties{};
	Animator m_AnimatedSprite{};
	BoxCollider* m_BoxCollider{ nullptr };

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	BoxCollider* GetCollider();

	sf::Vector2f GetPosition() const;

	unsigned GetDamagedDealt() const;
	ELEMENTTYPE GetElement() const;

	PROJECTILETYPE GetProjectileType() const;

	bool IsDestroyedOnCollision() const;
	bool DoesApplyElementToTarget() const;
};

