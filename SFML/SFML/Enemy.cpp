// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Enemy.cpp 
// Description : Enemy class
// Author : Inman, Will; Frear, Stace
// Mail : 

// Includes
#include "Enemy.h"
#include "Math.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "Player.h"
#include "PlayerManager.h"
#include "TextureLoader.h"
#include "VFX.h"

Enemy::Enemy(EnemyProperties _properties)
{
	// Set animation for enemy from sprite sheet
	AnimStateProperties animProperties;
	animProperties.StateTexture = _properties.Texture;
	animProperties.NumberOfFrames = 4;
	animProperties.FrameInterval = 0.1f;
	animProperties.Loops = true;
	animProperties.Scale = _properties.v2fMoveScale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");
	m_AnimatedSprite.GetSprite().setPosition(_properties.StartPos);
	m_AnimatedSprite.StartState("Moving");
	
	// Set enemy properties
	m_Properties = _properties;
	SetHPMax();
	m_fMoveSpeed = _properties.fMoveSpeed;
	m_fJumpSpeed = _properties.fJumpSpeed;
	
	//m_v2fSpriteJumpScale = _properties.v2fJumpScale;
	
	// Set box collider
	m_BoxCollider = new BoxCollider(sf::Vector2f(32, 24), { m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f });
}

Enemy::~Enemy()
{
	// Play explosion VFX animation
	SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/explosion.png") };
	explosionProperties.Scale = { 2.0f, 2.0f };
	explosionProperties.StartPos = m_AnimatedSprite.GetPosition();
	explosionProperties.NumberOfFrames = 9;
	explosionProperties.AnimFrameInterval = 0.5f / 9;
	explosionProperties.Velocity = {0.0f, 160.0f };
	VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.5f);
}

void Enemy::Update()
{
	Movement(); // Update enemy movement
	m_AnimatedSprite.Update(); // Update animated sprite

	if (m_bDamaged)
	{
		// Change sprite color
		m_fSpriteChangeColorCounter -= 1 * Statics::fDeltaTime; // Count down
		if (m_fSpriteChangeColorCounter <= 0)
		{
			m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
			m_bSpriteColorChanged = !m_bSpriteColorChanged;
		}

		if (m_bSpriteColorChanged)
			m_AnimatedSprite.SetSpriteColor(m_DamagedSpriteColor);
		else
			m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255));

		m_fOneSecond -= 1 * Statics::fDeltaTime; // Count down

		if (m_fOneSecond <= 0) // Do below every second
		{
			// Destroy enemy if health is <= 0
			if (m_iCurrentHealth <= 0)
			{
				m_bDestroy = true;
			}

			m_fOneSecond = 1.0f; // Reset OneSecond variable for counting
			m_fDamageTime -= 1; // Countdown the damage time variable by one second

			// Stop damage over time
			if (m_fDamageTime <= 0)
			{
				m_bDamaged = false;
				m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255)); // Reset sprite color
			}
		}
	}
	
	if (m_bFrozen)
	{
		m_fFreezeTime -= 1 * Statics::fDeltaTime; // Count down

		if (m_fFreezeTime <= 0)
		{
			m_bFrozen = false;
			m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255)); // Change color back to normal sprite 
			// Reset movement and jump speed
			m_fMoveSpeed = m_Properties.fMoveSpeed;
			m_fJumpSpeed = m_Properties.fJumpSpeed;
			// Resume animations
			m_AnimatedSprite.ResumeAnim();
		}
	}

	if (m_bSlowed)
	{
		// Change sprite color
		m_fSpriteChangeColorCounter -= 1 * Statics::fDeltaTime; // Count down
		if (m_fSpriteChangeColorCounter <= 0)
		{
			m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
			m_bSpriteColorChanged = !m_bSpriteColorChanged;
		}

		if (m_bSpriteColorChanged)
			m_AnimatedSprite.SetSpriteColor(m_SlowedSpriteColor);
		else
			m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255));

		m_fSlowTime -= 1 * Statics::fDeltaTime; // Count down

		if (m_fSlowTime <= 0)
		{
			m_bSlowed = false;
			m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255)); // Change color back to normal sprite 
			// Reset movement and jump speed
			m_fJumpSpeed = m_Properties.fJumpSpeed;
			m_fMoveSpeed = m_Properties.fMoveSpeed;
		}
	}
}

sf::Vector2f Enemy::GetPosition() const
{
	return m_Mesh.getPosition();
}

void Enemy::SetPosition(sf::Vector2f _newPosition)
{
	m_Mesh.setPosition(_newPosition);
}

sf::Sprite Enemy::GetSprite() const
{
	return m_Mesh;
}

void Enemy::TakeDamage(unsigned _amount)
{
	m_iCurrentHealth -= _amount; // Lower current health by provided parameter

	// Destroy enemy if health is <= 0
	if (m_iCurrentHealth <= 0)
	{
		m_bDestroy = true;
	}
}

void Enemy::Heal(unsigned _amount)
{
	// Increase enemy health by amount provided by parameter
	for (short i = _amount; m_iCurrentHealth < m_Properties.iMaxHealth; i--)
	{
		m_iCurrentHealth++;
	}
}

void Enemy::DamageEnemyOverTime(unsigned _damagePerSecond, float _seconds)
{
	m_fSpriteChangeColorSpeed = 0.2f;
	m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
	m_bSpriteColorChanged = true;
	m_bDamaged = true;
	m_uDamageOverTime = _damagePerSecond;
	m_fDamageTime = _seconds;
}

void Enemy::FreezeEnemy(float _seconds)
{
	// Stop enemy movement
	m_fMoveSpeed = Statics::fBackgroundScrollSpeed;
	m_fJumpSpeed = Statics::fBackgroundScrollSpeed;

	// Change sprite color
	m_AnimatedSprite.SetSpriteColor(m_FrozenSpriteColor);

	// Pause animations
	m_AnimatedSprite.PauseAnim();

	m_bSpriteColorChanged = true;
	m_bFrozen = true;
	m_fFreezeTime = _seconds;
}

void Enemy::SlowEnemy(float _seconds, float _slowMovementPercentage)
{
	// Slow enemy movement by percentage
	m_fMoveSpeed = m_fMoveSpeed * _slowMovementPercentage;
	m_fJumpSpeed = m_fJumpSpeed * _slowMovementPercentage;

	m_fSpriteChangeColorSpeed = 0.5f;
	m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
	m_bSpriteColorChanged = true;
	m_bSlowed = true;
	m_fSlowTime = _seconds;
}

int Enemy::GetCurrentHealth() const
{
	return m_iCurrentHealth;
}

void Enemy::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_AnimatedSprite); // Draw sprite

	// Draw box collider if debug mode turned on
	m_BoxCollider->DrawDebug(_target); 
}

void Enemy::SetHPMax()
{
	m_iCurrentHealth = m_Properties.iMaxHealth;
}

void Enemy::Movement()
{
	m_v2fVelocity = { 0,1 };

	switch (m_Properties.EnemyType)
	{
		// Movement of Kamikaze enemy
		// Runs straight down, and jumps over obstacles 
		case ENEMYTYPE::KAMIKAZE: 
		{
			// Checking collisions with obstacles
			m_BoxCollider->bColliding = false;
			for (unsigned i = 0; i < ObjectManager::GetInstance().GetObstacles().size(); i++)
			{
				if (m_BoxCollider->CheckCollision(ObjectManager::GetInstance().GetObstacles()[i]->GetCollisionBox()))
				m_BoxCollider->bColliding = true;
			}

			if (m_BoxCollider->bColliding)
			{
				m_AnimatedSprite.SetScale(m_Properties.v2fJumpScale);
				m_AnimatedSprite.MoveSprite(m_v2fVelocity * m_fJumpSpeed * Statics::fDeltaTime);

			}
			else
			{
				m_AnimatedSprite.SetScale(m_Properties.v2fMoveScale);
				m_AnimatedSprite.MoveSprite(m_v2fVelocity * m_fMoveSpeed * Statics::fDeltaTime);
			}

			// Checking collisions with players
			for (unsigned i = 0; i < PlayerManager::GetInstance().GetPlayers().size(); i++)
			{
				if (m_BoxCollider->CheckCollision(PlayerManager::GetInstance().GetPlayers()[i]->GetCollisionBox()))
				{
					// --Testing--
					//PlayerManager::GetInstance().GetPlayers()[i]->TakeDamage(100);
					//DamageEnemyOverTime(1, 3.0f);
					//FreezeEnemy(3.0f);
					//SlowEnemy(3.0f, 0.75f);
					
					m_iCurrentHealth = 0; // Instantly kill enemy
					PlayerManager::GetInstance().GetPlayers()[i]->TakeDamage(1);
				}
			}

			// Update collider position
			m_BoxCollider->UpdatePosition({ m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f });
		}
	}
}

void Enemy::Attack()
{
	m_fAttackTimer -= Statics::fDeltaTime;
	if (m_fAttackTimer <= 0)
	{
		m_fAttackTimer = m_fAttackSpeed;
		ProjectileManager::GetInstance().CreateProjectile(
			{
				&TextureLoader::LoadTexture("Projectile.png"),
				GetPosition(),
				{0.25f,0.25f},
				false
			}
		);
	}
}


