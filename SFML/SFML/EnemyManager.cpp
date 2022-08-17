#include "EnemyManager.h"
#include "Enemy.h"
#include "PlayerManager.h"
#include "Player.h"

void EnemyManager::CleanupDestroyed()
{
	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		if ((*enemyIt)->Destroy == true)
		{
			if ((*enemyIt) != nullptr)
			{
				delete (*enemyIt);
				(*enemyIt) = nullptr;
			}
			enemyIt = m_Enemies.erase(enemyIt);
			continue;
		}
		enemyIt++;
	}
}

void EnemyManager::CleanupEnemies()
{
	for (auto& enemy : m_Enemies)
	{
		if (enemy != nullptr)
		{
			delete enemy;
			enemy = nullptr;
		}
	}
	m_Enemies.clear();
	m_Enemies.resize(0);
}

void EnemyManager::CreateEnemy(EnemyProperties _properties)
{
	m_Enemies.emplace_back(new Enemy(_properties));
}

void EnemyManager::Update()
{
	SpawnEnemies(1.0f);

	for(auto& enemy : m_Enemies)
	{
		if (enemy->GetCurrentHealth() <= 0)
		{
			enemy->Destroy = true;
		}
		else
		{
			for (auto& player : PlayerManager::GetInstance().GetPlayers())
			{
				if (player != nullptr)
				{
					if (enemy->CheckCollision(player->GetSprite()))
					{
						player->TakeDamage(1);

						enemy->Destroy = true;
						break;
					}
				}
			}
		}
		enemy->Update();
	}
}

std::vector<sf::Sprite> EnemyManager::GetEnemySprites() const
{
	std::vector<sf::Sprite> sprites{};
	for (auto& enemy : m_Enemies)
	{
		sprites.emplace_back(enemy->GetSprite());
	}
	return sprites;
}

std::vector<Enemy*>& EnemyManager::GetEnemies()
{
	return m_Enemies;
}

void EnemyManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& enemy : m_Enemies)
	{
		_target.draw(*enemy);
	}
}

void EnemyManager::SpawnEnemies(float _rate)
{
	m_SpawnTimer -= Statics::DeltaTime;
	if (m_SpawnTimer <= 0)
	{
		m_SpawnTimer = _rate;
		CreateEnemy(
			{
				&TextureLoader::LoadTexture("Goblin.png"),
				{100.0f + (rand() % 600), 0},
				{2,2}
			});
	}
}