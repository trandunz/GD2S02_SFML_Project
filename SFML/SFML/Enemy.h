// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Enemy.h 
// Description : Enemy class
// Author : Inman, Will; Frear, Stace
// Mail : 

#pragma once

// Includes
#include "Animator.h"

class BoxCollider;
class Enemy : public sf::Drawable
{
public:
	/// <summary>
	/// Constructor
	/// 
	/// Sets the animated sprite for the enemy
	/// Sets all member variables from the static properties
	/// Creates the box collider
	/// </summary>
	/// <param name="_properties"></param>
	Enemy(EnemyProperties _properties);

	/// <summary>
	/// Runs code related to enemy destruction, in particular
	/// any VFX or sprite changes on enemy death
	/// </summary>
	~Enemy();

	/// <summary>
	/// Updates enemy each tick
	/// </summary>
	void Update();

	/// <summary>
	/// Decrease enemy health by the amount
	/// provided by the parameter
	/// </summary>
	/// <param name="_amount"></param>
	void TakeDamage(unsigned _amount);

	/// <summary>
	/// Increase enemy health by the amount
	/// provided by the parameter
	/// </summary>
	/// <param name="_amount"></param>
	void Heal(unsigned _amount);

	void DamageEnemyOverTime(unsigned _damagePerSecond, float _seconds);

	void FreezeEnemy(float _seconds);

	void SlowEnemy(float _seconds, float _slowMovementPercentage);

	bool CheckCollision(BoxCollider& _otherCollider);

	bool m_bDestroy = false;

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Sets enemy health based on the static properties
	/// </summary>
	void SetHPMax();

	/// <summary>
	/// Runs all code related to enemy movement
	/// Includes a switch case and provides different movement
	/// based on the enemy type
	/// </summary>
	void Movement();

	/// <summary>
	/// Creates a projectile from the enemy position that shoots
	/// straight down towards players
	/// </summary>
	void Attack();

	EnemyProperties m_Properties{};
	float m_fAttackSpeed{ 1.0f };
	float m_fAttackTimer{};
	sf::Sprite m_Mesh{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
	//sf::Vector2f m_v2fSpriteJumpScale{};
	float m_fMoveSpeed{};
	float m_fJumpSpeed{};

	// Status effect related variables
	// -Damage over time on enemy variables-
	bool m_bDamaged;
	unsigned m_uDamageOverTime;
	float m_fOneSecond = 1.0f;
	float m_fDamageTime;
	sf::Color m_DamagedSpriteColor = sf::Color(255, 23, 23);
	// -Enemy being frozen variables (unable to move)-
	bool m_bFrozen; 
	float m_fFreezeTime;
	sf::Color m_FrozenSpriteColor = sf::Color(0, 162, 232);
	// -Enemy being slowed variables-
	bool m_bSlowed; 
	float m_fSlowTime;
	sf::Color m_SlowedSpriteColor = sf::Color(181, 230, 29);

	// Changing sprite color
	bool m_bSpriteColorChanged = false;
	float m_fSpriteChangeColorSpeed = 0.2f; // Color changing speed
	float m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed; // Color changing timer
	
	BoxCollider* m_BoxCollider;

	Animator m_AnimatedSprite{};

public:
	// Getters and Setters
	ENEMYTYPE GetType();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f _newPosition);

	sf::Sprite GetSprite() const;

	int GetCurrentHealth() const;

	BoxCollider* GetCollider();
};