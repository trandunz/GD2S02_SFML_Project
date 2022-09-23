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
	Projectile(ProjectileProperties _properties);
	~Projectile();

	void Update();

	/// <summary>
	/// Bool to indicate if collides with player
	/// </summary>
	/// <returns></returns>
	bool IsFriendly() const;

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

	sf::Vector2f GetPosition() const;

	unsigned GetDamagedDealt() const;
	ELEMENTTYPE GetElement() const;

	bool IsDestroyedOnCollision() const;
};

