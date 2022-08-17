#include "Enemy.h"

Enemy::Enemy(EnemyProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	m_Properties.MoveSpeed = _properties.MoveSpeed;
	m_Properties.MaxHealth = _properties.MaxHealth;
	SetHPMax();
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
		Destroy = true;
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
}

void Enemy::SetHPMax()
{
	m_iCurrentHealth = m_Properties.MaxHealth;
}

void Enemy::Movement()
{
	m_v2fVelocity = { 0,1 };
	m_Mesh.move(m_v2fVelocity * m_Properties.MoveSpeed * Statics::DeltaTime);
}

void Enemy::Attack()
{
	m_AttackTimer -= Statics::DeltaTime;
	if (m_AttackTimer <= 0)
	{
		m_AttackTimer = m_AttackSpeed;
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
