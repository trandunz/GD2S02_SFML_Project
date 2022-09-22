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

	bool CheckCollision(BoxCollider& _otherCollider);

	bool Destroy = false;
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	
	ProjectileProperties m_Properties{};
	Animator m_AnimatedSprite{};
	BoxCollider* m_BoxCollider{ nullptr };
	//sf::Sprite m_Mesh{};

public:
	sf::Vector2f GetPosition() const;

	bool IsFriendly() const;
};

