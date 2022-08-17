#pragma once
#include "ProjectileManager.h"
#include "Math.h"

class Enemy : public sf::Drawable
{
public:
	Enemy(EnemyProperties _properties);
	~Enemy();

	void Update();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f _newPosition);

	sf::Sprite GetSprite() const;

	void TakeDamage(unsigned _amount);
	void Heal(unsigned _amount);

	int GetCurrentHealth() const;

	bool CheckCollision(sf::Sprite _entitySprite);

	bool Destroy = false;

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	void SetHPMax();

	void Movement();
	void Attack();

	EnemyProperties m_Properties;
	float m_AttackSpeed{ 1.0f };
	float m_AttackTimer{ 0.0f };
	sf::Sprite m_Mesh{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
};

