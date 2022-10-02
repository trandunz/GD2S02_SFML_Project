// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Enemy.cpp 
// Description : Enemy Implementation File
// Author : Inman, Will; Frear, Stace

// Includes
#include "Enemy.h"
#include "Math.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "Player.h"
#include "PlayerManager.h"
#include "TextureLoader.h"
#include "VFX.h"
#include "BoxCollider.h"
#include "ProjectileManager.h"

Enemy::Enemy(EnemyProperties _properties)
{
	// Set enemy properties
	m_Properties = _properties;
	SetHPMax();
	m_fMoveSpeed = _properties.fMoveSpeed;
	m_fJumpSpeed = _properties.fJumpSpeed;

	// Set animation for enemy from sprite sheet
	AnimStateProperties animProperties;
	animProperties.StateTexture = _properties.Texture;

	switch (m_Properties.EnemyType)
	{
		case ENEMYTYPE::KAMIKAZE:
		{
			animProperties.uNumberOfFrames = 4;
			animProperties.fFrameInterval = 0.1f;
			break;
		}
		case ENEMYTYPE::ARCHER:
		{
			animProperties.uNumberOfFrames = 4;
			animProperties.fFrameInterval = 0.1f;

			m_fArcherYPos = (rand() % 261) + 70.0f;
			std::cout << m_fArcherYPos << std::endl;
			break;
		}
		default:
			break;
	}

	animProperties.bLoops = true;
	animProperties.v2fScale = _properties.v2fMoveScale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");
	m_AnimatedSprite.GetSprite().setPosition(_properties.v2fStartPos);
	m_AnimatedSprite.StartState("Moving");
	
	//m_v2fSpriteJumpScale = _properties.v2fJumpScale;
	
	// Set box collider
	m_BoxCollider = new BoxCollider(sf::Vector2f(32, 24), { m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f });
}

Enemy::~Enemy()
{
	switch (m_Properties.EnemyType)
	{
	case ENEMYTYPE::KAMIKAZE:
	{
		// Play explosion VFX animation
		SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/explosion.png") };
		explosionProperties.v2fScale = { 2.0f, 2.0f };
		explosionProperties.v2fStartPos = m_AnimatedSprite.GetPosition();
		explosionProperties.uNumberOfFrames = 9;
		explosionProperties.fAnimFrameInterval = 0.5f / 9;
		explosionProperties.v2fVelocity = { 0.0f, 160.0f };
		VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.5f);
		break;
	}
	case ENEMYTYPE::ARCHER:
	{
		// Play archer death VFX animation
		SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("VFX/Goblin_Archer_Death.png") };
		explosionProperties.v2fScale = { 2.0f, 2.0f };
		explosionProperties.v2fStartPos = m_AnimatedSprite.GetPosition();
		explosionProperties.uNumberOfFrames = 5;
		explosionProperties.fAnimFrameInterval = 0.5f / 5;
		explosionProperties.v2fVelocity = { 0.0f, 0.0f };
		VFX::GetInstance().CreateAndPlayEffect(explosionProperties, 0.5f);
		break;
	}
	default:
		break;
	}
	
}

void Enemy::Update()
{
	Movement(); // Update enemy movement

	if (m_Properties.EnemyType == ENEMYTYPE::ARCHER)
		Attack();

	m_AnimatedSprite.Update(); // Update animated sprite

	// If enemy is damaged from fire spell, then run function to damage over time
	if (m_bDamaged)
	{
		HandleDamageOverTime();
	}
	// If enemy is hit from freeze spell, then run function for freezing said enemy
	if (m_bStopped)
	{
		HandleStop();
	}
	// If enemy is hit from earth spell, then run function to slow enemy
	if (m_bSlowed)
	{
		HandleSlow();
	}

	// Update collider position
	m_BoxCollider->SetPosition({ m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f });
}

ENEMYTYPE Enemy::GetType()
{
	return m_Properties.EnemyType;
}

sf::Vector2f Enemy::GetPosition() const
{
	return m_AnimatedSprite.GetPosition();
}

void Enemy::SetPosition(sf::Vector2f _newPosition)
{
	m_AnimatedSprite.SetPosition(_newPosition);
}

sf::Sprite Enemy::GetSprite() const
{
	return m_Mesh;
}

void Enemy::TakeDamage(unsigned _amount)
{
	m_iCurrentHealth -= _amount; // Lower current health by provided parameter

	// bDestroy enemy if health is <= 0
	if (m_iCurrentHealth <= 0)
	{
		bDestroy = true;
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

void Enemy::ApplyDamageOverTime(unsigned _damagePerSecond, float _seconds, sf::Color _color)
{
	m_DamagedSpriteColor = _color;
	m_fSpriteChangeColorSpeed = 0.2f;
	m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
	m_bSpriteColorChanged = true;
	m_bDamaged = true;
	m_uDamageOverTime = _damagePerSecond;
	m_fDamageTime = _seconds;
}

void Enemy::ApplyStop(float _seconds, sf::Color _color)
{
	// Stop enemy movement
	m_fMoveSpeed = Statics::fBackgroundScrollSpeed;
	m_fJumpSpeed = Statics::fBackgroundScrollSpeed;

	// Change sprite color
	m_AnimatedSprite.SetSpriteColor(_color);

	// Pause animations
	m_AnimatedSprite.PauseAnim();

	m_bSpriteColorChanged = true;
	m_bStopped = true;
	m_fStopTime = _seconds;
}

void Enemy::ApplySlow(float _seconds, float _slowMovementPercentage, sf::Color _color)
{
	// Slow enemy movement by percentage
	m_fMoveSpeed = m_fMoveSpeed * _slowMovementPercentage;
	m_fJumpSpeed = m_fJumpSpeed * _slowMovementPercentage;

	m_SlowedSpriteColor = _color;
	m_fSpriteChangeColorSpeed = 0.5f;
	m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
	m_bSpriteColorChanged = true;
	m_bSlowed = true;
	m_fSlowTime = _seconds;
}

BoxCollider* Enemy::GetCollider() const
{
	if (m_BoxCollider)
	{
		return m_BoxCollider;
	}
	else
	{
		return nullptr;
	}
}

Animator Enemy::GetAnimation() const
{
	return m_AnimatedSprite;
}

bool Enemy::CheckCollision(BoxCollider& _otherCollider)
{
	if (m_BoxCollider)
	{
		return m_BoxCollider->CheckCollision(_otherCollider);
	}
	else
	{
		return false;
	}
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
	switch (m_Properties.EnemyType)
	{
		// Movement of Kamikaze enemy
		// Runs straight down, and jumps over obstacles 
		case ENEMYTYPE::KAMIKAZE: 
		{
			m_v2fVelocity = { 0,1 };

			// Checking collisions with obstacles
			m_BoxCollider->bColliding = false;
			for (auto& obstacle : ObjectManager::GetInstance().GetObstacles())
			{
				if (m_BoxCollider->CheckCollision(*obstacle->GetCollisionBox()))
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
			break;
		}
		// Movement of Archer enemy
		// Runs down until it reaches m_fArcherYPos, then starts moving left and right
		case ENEMYTYPE::ARCHER:
		{
			// Move enemy object down to therandom Y position determined in the constructor
			if (m_AnimatedSprite.GetPosition().y <= m_fArcherYPos)
			{
				m_v2fVelocity = { 0,1 };
			}
			// If enemy object reaches its Y value, then start moving left or right
			else if (m_bFirstMoveComplete == false)
			{
				m_v2fVelocity = { 1,0 }; // Move right
			}

			// If enemy object moves to the right side of the screen, then switch its velocity to move left
			if (m_AnimatedSprite.GetPosition().x >= Statics::RenderWindow.getSize().x - (m_AnimatedSprite.GetSprite().getGlobalBounds().width / 2))
			{
				m_v2fVelocity = { -1,0 };
				m_bFirstMoveComplete = true;
			}
			
			// If enemy object moves to the left side of the screen, then switch its velocity to move right
			if (m_AnimatedSprite.GetPosition().x <= 0 + (m_AnimatedSprite.GetSprite().getGlobalBounds().width / 2))
			{
				m_v2fVelocity = { 1,0 };
			}

			// Checking collisions with obstacles
			m_BoxCollider->bColliding = false;
			for (auto& obstacle : ObjectManager::GetInstance().GetObstacles())
			{
				if (m_BoxCollider->CheckCollision(*obstacle->GetCollisionBox()))
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
			break;
		}
		default:
			m_v2fVelocity = { 0,1 };
			break;
	}
}

void Enemy::Attack()
{
	m_fAttackTimer -= Statics::fDeltaTime;
	if (m_fAttackTimer <= 0)
	{
		// Pick a random attack speed based on the speed provided in the enemy creation
		// The reason for is, is to give the enemy shooting some randomness, as otherwise all enemies shoot
		// at the exact same time, which does not look right
		unsigned uRandomNumber = rand() % 3; // Random number out of 3
		float fAttackSpeed;
		if (uRandomNumber == 0)
			fAttackSpeed = m_fAttackSpeed;
		else if (uRandomNumber == 1)
			fAttackSpeed = m_fAttackSpeed - 0.1f;
		else
			fAttackSpeed = m_fAttackSpeed + 0.1f;

		m_fAttackTimer = fAttackSpeed; // Reset timer
		// Create projectile
		ProjectileManager::GetInstance().CreateProjectile(
			{
				&TextureLoader::LoadTexture("Projectiles/Goblin_Archer_Arrow.png"),
				{GetPosition().x + 16.0f,GetPosition().y + 8.0f},
				{2.0f,2.0f},
				false,
				{1},
				500.0f
			}
		);
	}
}

void Enemy::HandleDamageOverTime()
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
		// bDestroy enemy if health is <= 0
		if (m_iCurrentHealth <= 0)
		{
			bDestroy = true;
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

void Enemy::HandleStop()
{
	m_fStopTime -= 1 * Statics::fDeltaTime; // Count down

	if (m_fStopTime <= 0)
	{
		m_bStopped = false;
		m_AnimatedSprite.SetSpriteColor(sf::Color(255, 255, 255)); // Change color back to normal sprite 
		// Reset movement and jump speed
		m_fMoveSpeed = m_Properties.fMoveSpeed;
		m_fJumpSpeed = m_Properties.fJumpSpeed;
		// Resume animations
		m_AnimatedSprite.ResumeAnim();
	}
}

void Enemy::HandleSlow()
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
