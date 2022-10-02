// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : EnemyManager.cpp 
// Description : EnemyManager Implementation File		
// Author : Inman, Will

#include "EnemyManager.h"
#include "Enemy.h"
#include "PlayerManager.h"
#include "Player.h"
#include "TextureLoader.h"
#include "Helper.h"
#include "AudioManager.h"

EnemyManager& EnemyManager::GetInstance()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::CleanupDestroyed()
{
	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		if ((*enemyIt)->bDestroy == true)
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
	CleanupVector(m_Enemies);
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
		// bDestroy enemy if its health is equal or less than 0
		if (enemy->GetCurrentHealth() <= 0)
		{
			Statics::fGameScore += 20.0f; // Increase game score
			enemy->bDestroy = true;
			
			AudioManager::PlayAudioSource("EnemyDeath");
		}
		// bDestroy enemies if they below the screen
		else if (enemy->GetPosition().y >= Statics::RenderWindow.getSize().y + m_fDestroyDistanceY)
		{
			enemy->bDestroy = true;
		}
		else
		{
			for (auto& player : PlayerManager::GetInstance().GetPlayers())
			{
				if (player)
				{
					if (enemy->CheckCollision(*player->GetCollisionBox()))
					{
						switch (enemy->GetType())
						{
						case ENEMYTYPE::KAMIKAZE:
						{
							player->TakeDamage(1);
							enemy->bDestroy = true;
							AudioManager::PlayAudioSource("EnemyDeath");
							break;
						}
						default:
							break;
						}

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
	m_fSpawnTimer -= Statics::fDeltaTime;
	if (m_fSpawnTimer <= 0)
	{
		m_fSpawnTimer = _rate;

		int iRandomEnemy = rand() % 6;
		// Create Archer
		if (iRandomEnemy == 0)
		{
			CreateEnemy(
				{
					&TextureLoader::LoadTexture("Unit/Enemy/Goblin_Archer_Running.png"),
					{100.0f + (rand() % 600), 0},
					{ENEMYTYPE::ARCHER},
					{2.0f,2.0f},
					{2.4f,2.4f},
					{150.0f},
					{250.0f}
				});
		}
		// Create Warrior
		else if (iRandomEnemy == 1 || iRandomEnemy == 2)
		{
			CreateEnemy(
				{
					&TextureLoader::LoadTexture("Unit/Enemy/Goblin_Warrior_Running.png"), // Set warrior running sprite
					{100.0f + (rand() % 600), 0}, // Set random starting position
					{ENEMYTYPE::WARRIOR}, // Set enemy type - Warrior
					{2.0f,2.0f}, // Warrior sprite size
					{0.0f,0.0f}, // Warrior does not jump
					{300.0f}, // Faster run speed
					{0.0f}, // Warrior does not jump
					{10} // High health
				});
		}
		// Create Kamakazi
		else
		{
			int iRandomKamakazi = rand() % 5;
			std::string sEnemyTextureLocation;
			if (iRandomKamakazi == 0)
			{
				sEnemyTextureLocation = "Unit/Enemy/Goblin_Kamakazi_Running1.png";
			}
			else if (iRandomKamakazi == 1)
			{
				sEnemyTextureLocation = "Unit/Enemy/Goblin_Kamakazi_Running2.png";
			}
			else if (iRandomKamakazi == 2)
			{
				sEnemyTextureLocation = "Unit/Enemy/Goblin_Kamakazi_Running3.png";
			}
			else if (iRandomKamakazi == 3)
			{
				sEnemyTextureLocation = "Unit/Enemy/Goblin_Kamakazi_Running4.png";
			}
			else
			{
				sEnemyTextureLocation = "Unit/Enemy/Goblin_Kamakazi_Running5.png";
			}

			CreateEnemy(
				{
					&TextureLoader::LoadTexture(sEnemyTextureLocation),
					{100.0f + (rand() % 600), 0},
					{ENEMYTYPE::KAMIKAZE},
					{2.0f,2.0f},
					{2.4f,2.4f}
				});
		}
	}
}