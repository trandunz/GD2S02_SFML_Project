#include "Enemy.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Math.h"
#include "TextureLoader.h"
#include "VFX.h"

Enemy::Enemy(EnemyProperties _properties)
{
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
	//m_Mesh.setTexture(*_properties.Texture, true);
	//SetOriginCenter(m_Mesh);
	//SetPosition(_properties.StartPos);
	//m_Mesh.setScale(_properties.Scale);
	m_Properties = _properties;
	SetHPMax();
	m_v2fSpriteJumpScale = _properties.Scale * 1.2f;
	m_fJumpSpeed = _properties.fMoveSpeed * 1.4f;

	// Set box collider
	m_BoxCollider = new BoxCollider(sf::Vector2f(32, 24), sf::Vector2f(m_AnimatedSprite.GetPosition().x, m_AnimatedSprite.GetPosition().y + 8.0f));
}

Enemy::~Enemy()
{
	VFX::GetInstance().CreateAndPlayEffect("Explosion",
		{ &TextureLoader::LoadTexture("explosion.png"),
		m_AnimatedSprite.GetPosition() }, 0.5f);

}

void Enemy::Update()
{
	Movement();
	m_AnimatedSprite.Update();
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
	m_iCurrentHealth -= _amount;

	if (m_iCurrentHealth <= 0)
	{
		m_bDestroy = true;
	}
}

void Enemy::Heal(unsigned _amount)
{
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
	//_target.draw(m_Mesh);
	_target.draw(m_AnimatedSprite);

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
				//m_Mesh.setScale(m_v2fSpriteJumpScale);
				//m_Mesh.move(m_v2fVelocity * m_fJumpSpeed * Statics::fDeltaTime);
				m_AnimatedSprite.SetScale(m_v2fSpriteJumpScale);
				m_AnimatedSprite.MoveSprite(m_v2fVelocity * m_fJumpSpeed * Statics::fDeltaTime);

			}
			else
			{
				//m_Mesh.setScale(m_Properties.Scale);
				//m_Mesh.move(m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
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
