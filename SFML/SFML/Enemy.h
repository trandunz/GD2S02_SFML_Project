// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Enemy.h 
// Description : Enemy Header File
// Author : Inman, Will; Frear, Stace

#pragma once
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

	/// <summary>
	/// Sets the enemy to start taking damage over time
	/// Flips a bool that runs the private function HandleDamageOverTime()
	/// that is run through the update per tick.
	/// Parameters set the damage per second this enemy will receive,
	/// for how long it will receive damage, and the color to flash
	/// while taking damage.
	/// </summary>
	/// <param name="_damagePerSecond"></param>
	/// <param name="_seconds"></param>
	/// <param name="_color"></param>
	void ApplyDamageOverTime(unsigned _damagePerSecond, float _seconds, sf::Color _color = { 255, 23, 23 });
	void FlashWhenHit();

	/// <summary>
	/// Sets the enemy to stop moving/shooting
	/// Flips a bool that runs the private function HandleStop()
	/// that is run through the update per tick.
	/// Parameters sets the amount of time to stop moving,
	/// and the color the sprite will change to. 
	/// Can be used for freezing or stunning enemies
	/// </summary>
	/// <param name="_seconds"></param>
	/// <param name="_color"></param>
	void ApplyStop(float _seconds, sf::Color _color = { 0, 162, 232 });

	/// <summary>
	/// Sets the enemy to slow movement/shooting
	/// Flips a bool that runs the private function HandleSlow
	/// that is run through the update per tick.
	/// Parameters sets the amount of time to slow movement,
	/// and the color the sprite will change to. 
	/// </summary>
	/// <param name="_seconds"></param>
	/// <param name="_slowMovementPercentage"></param>
	/// <param name="_color"></param>
	void ApplySlow(float _seconds, float _slowMovementPercentage, sf::Color _color = { 181, 230, 29 });

	/// <summary>
	/// Checks collision between enemy and another collider
	/// </summary>
	/// <param name="_otherCollider"></param>
	/// <returns></returns>
	bool CheckCollision(BoxCollider& _otherCollider);

	bool bDestroy{ false }; // Bool for holding enemies life/death status. If false, enemy manager will destroy object

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

	/// <summary>
	/// Handles the damage over time of the enemy for the specified 
	/// amount of time from the ApplyDamageOverTime function
	/// </summary>
	void HandleDamageOverTime();

	/// <summary>
	/// Handles the stopping of the enemy for the specified amount of time
	/// from the ApplyFreeze function (example freeze or stun)
	/// </summary>
	void HandleStop();

	/// <summary>
	/// Handles the slowing of the enemy for the specified amount of time
	/// from the ApplySlow function
	/// </summary>
	void HandleSlow();

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
	bool m_bDamaged{false};
	unsigned m_uDamageOverTime{};
	float m_fOneSecond{ 1.0f };
	float m_fDamageTime{};
	sf::Color m_DamagedSpriteColor;
	// -Enemy being frozen variables (unable to move)-
	bool m_bStopped{false};
	float m_fStopTime{};
	// -Enemy being slowed variables-
	bool m_bSlowed{false};
	float m_fSlowTime{};
	sf::Color m_SlowedSpriteColor;

	// Changing sprite color for status effects
	bool m_bSpriteColorChanged{ false };
	float m_fSpriteChangeColorSpeed{ 0.2f }; // Color changing speed
	float m_fSpriteChangeColorCounter{ m_fSpriteChangeColorSpeed }; // Color changing timer

	// Extra variables for archer enemy.
	// Used for setting Y position archer will move down to, before 
	// moving left and right
	float m_fArcherYPos{};
	float m_fShamanYPos{};
	bool m_bFirstMoveComplete{ false };
	
	BoxCollider* m_BoxCollider{nullptr}; // Enemy box collider

	Animator m_AnimatedSprite{}; // Enemy animation

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	ENEMYTYPE GetType();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f _newPosition);

	sf::Sprite GetSprite() const;

	int GetCurrentHealth() const;

	BoxCollider* GetCollider() const;

	Animator GetAnimation() const;

	BoxCollider* GetCollisionBox();
};