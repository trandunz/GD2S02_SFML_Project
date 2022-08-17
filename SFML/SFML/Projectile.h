#pragma once
#include "Statics.h"
#include "Math.h"

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
	
	ProjectileProperties m_Properties;
	sf::Sprite m_Mesh{};
};

