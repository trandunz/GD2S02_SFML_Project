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
	animProperties.Scale = _properties.Scale;
	m_AnimatedSprite.AddState("Moving", animProperties);
	m_AnimatedSprite.SetDefaultState("Moving");
	m_AnimatedSprite.GetSprite().setPosition(_properties.StartPos);
	m_AnimatedSprite.StartState("Moving");
	
	// Set enemy properties
	m_Properties = _properties;
	SetHPMax();
	m_v2fSpriteJumpScale = _properties.Scale * 1.2f;
	m_fJumpSpeed = _properties.fMoveSpeed * 1.4f;

	// Set box collider
	m_BoxCollider = new BoxCollider(sf::Vector2f(32, 24), sf::Vector2f(m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f));
}

Enemy::~Enemy()
{
	// Play explosion VFX animation
	SpecialEffectProperties explosionProperties{ &TextureLoader::LoadTexture("explosion.png") };
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
				m_AnimatedSprite.SetScale(m_v2fSpriteJumpScale);
				m_AnimatedSprite.MoveSprite(m_v2fVelocity * m_fJumpSpeed * Statics::fDeltaTime);

			}
			else
			{
				m_AnimatedSprite.SetScale(m_Properties.Scale);
				m_AnimatedSprite.MoveSprite(m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
			}

			// Checking collisions with players
			for (unsigned i = 0; i < PlayerManager::GetInstance().GetPlayers().size(); i++)
			{
				if (m_BoxCollider->CheckCollision(PlayerManager::GetInstance().GetPlayers()[i]->GetCollisionBox()))
				{
					m_iCurrentHealth = 0;
					//PlayerManager::GetInstance().GetPlayers()[i]->TakeDamage(1);
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
