#pragma once
#include "Animator.h"

class Projectile : public sf::Drawable
{
public:
	Projectile(ProjectileProperties _properties);
	~Projectile();

	void Update();

	bool CheckCollision(sf::Sprite _entitySprite);
	sf::Vector2f GetPosition() const;

	bool IsFriendly() const;

	bool Destroy = false;
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	
	ProjectileProperties m_Properties{};
	Animator m_AnimatedSprite{};
	//sf::Sprite m_Mesh{};
};

