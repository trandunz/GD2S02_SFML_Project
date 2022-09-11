#include "Enemy.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "Math.h"
#include "TextureLoader.h"

Enemy::Enemy(EnemyProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	m_Properties = _properties;
	SetHPMax();
	m_v2fSpriteJumpScale = _properties.Scale * 1.2f;
	m_fJumpSpeed = _properties.fMoveSpeed * 1.4f;

	// Set box collider
	m_BoxCollider = new BoxCollider(sf::Vector2f(32, 24), sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + 8.0f));
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Movement();
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

//bool Enemy::CheckCollision(sf::Sprite _entitySprite)
//{
//	return m_Mesh.getGlobalBounds().intersects(_entitySprite.getGlobalBounds());
//}

void Enemy::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);

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
			//bool bColliding = false;
			m_BoxCollider->bColliding = false;
			for (unsigned i = 0; i < ObjectManager::GetInstance().GetObstacles().size(); i++)
			{
				//if (CheckCollision(ObjectManager::GetInstance().GetObstacles()[i]->GetSprite()))
				if (m_BoxCollider->CheckCollision(ObjectManager::GetInstance().GetObstacles()[i]->GetCollisionBox()))
				m_BoxCollider->bColliding = true;
			}

			if (m_BoxCollider->bColliding)
			{
				m_Mesh.setScale(m_v2fSpriteJumpScale);
				m_Mesh.move(m_v2fVelocity * m_fJumpSpeed * Statics::fDeltaTime);
			}
			else
			{
				m_Mesh.setScale(m_Properties.Scale);
				m_Mesh.move(m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
			}

			// Update collider position
			m_BoxCollider->UpdatePosition({ m_Mesh.getPosition().x, m_Mesh.getPosition().y + 8.0f });
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
