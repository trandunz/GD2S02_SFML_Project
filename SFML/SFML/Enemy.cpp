#include "Enemy.h"
#include "ObjectManager.h"
#include "Obstacle.h"

Enemy::Enemy(EnemyProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	m_Properties = _properties;
	SetHPMax();
	m_v2fSpriteJumpScale = _properties.Scale * 1.2f;
	m_fJumpSpeed = _properties.MoveSpeed * 1.4f;

	m_rectangleCollision = new sf::RectangleShape(sf::Vector2f(32, 24));
	m_rectangleCollision->setPosition(m_Mesh.getPosition().x, m_Mesh.getPosition().y + 8.0f);
	m_rectangleCollision->setOrigin(m_rectangleCollision->getSize().x / 2, m_rectangleCollision->getSize().y / 2);
	m_rectangleCollision->setFillColor(sf::Color::Blue);
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
	for (short i = _amount; m_iCurrentHealth < m_Properties.MaxHealth; i--)
	{
		m_iCurrentHealth++;
	}
}

int Enemy::GetCurrentHealth() const
{
	return m_iCurrentHealth;
}

bool Enemy::CheckCollision(sf::Sprite _entitySprite)
{
	return m_Mesh.getGlobalBounds().intersects(_entitySprite.getGlobalBounds());
}

void Enemy::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
	//_target.draw(*m_rectangleCollision); // Draw rectangle collision box, only turn on when debugging
}

void Enemy::SetHPMax()
{
	m_iCurrentHealth = m_Properties.MaxHealth;
}

void Enemy::Movement()
{
	m_v2fVelocity = { 0,1 };

	switch (m_Properties.EnemyType)
	{
		case ENEMYTYPE::KAMIKAZE:
		{
			bool bColliding = false;
			for (unsigned i = 0; i < ObjectManager::GetInstance().GetObstacles().size(); i++)
			{
				if (CheckCollision(ObjectManager::GetInstance().GetObstacles()[i]->GetSprite()))
					bColliding = true;
			}

			if (bColliding)
			{
				m_Mesh.setScale(m_v2fSpriteJumpScale);
				m_Mesh.move(m_v2fVelocity * m_fJumpSpeed * Statics::DeltaTime);
			}
			else
			{
				m_Mesh.setScale(m_Properties.Scale);
				m_Mesh.move(m_v2fVelocity * m_Properties.MoveSpeed * Statics::DeltaTime);
			}
			m_rectangleCollision->setPosition(m_Mesh.getPosition().x, m_Mesh.getPosition().y + 8.0f);
		}
	}
}

void Enemy::Attack()
{
	m_fAttackTimer -= Statics::DeltaTime;
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
