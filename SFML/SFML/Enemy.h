// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Enemy.h 
// Description : Enemy class
// Author : 
// Mail : 

#pragma once
#include "ProjectileManager.h"
#include "BoxCollider.h"

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

	//bool CheckCollision(sf::Sprite _entitySprite);

	bool m_bDestroy = false;

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	void SetHPMax();

	void Movement();
	void Attack();

	EnemyProperties m_Properties{};
	float m_fAttackSpeed{ 1.0f };
	float m_fAttackTimer{};
	sf::Sprite m_Mesh{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
	sf::Vector2f m_v2fSpriteJumpScale{};
	float m_fJumpSpeed{};

	BoxCollider* m_BoxCollider;
};