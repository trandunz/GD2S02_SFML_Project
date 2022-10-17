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
#include "BoxCollider.h"
#include "LevelLoader.h"

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
				switch ((*enemyIt)->GetType())
				{
				case ENEMYTYPE::ARCHER:
				{
					m_iArcherCount--;
					break;
				}
				case ENEMYTYPE::WARRIOR:
				{
					m_iWarriorCount--;
					break;
				}
				case ENEMYTYPE::SHAMAN:
				{
					m_iShamanCount--;
					break;
				}
				case ENEMYTYPE::KAMIKAZE:
				{
					m_iKamikazeCount--;
					break;
				}
				default:
					break;
				}
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
		// Destroy enemy if its health is equal or less than 0
		if (enemy->GetCurrentHealth() <= 0)
		{
			Statics::fGameScore += enemy->GetPoints(); // Increase game score
			enemy->bDestroy = true; // Set enemy to die
			
			AudioManager::PlayAudioSource("EnemyDeath"); // Play enemy death SFX
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
					if (player->m_bInvincible == false)
					{
						if (enemy->CheckCollision(*player->GetCollisionBox()))
						{
							switch (enemy->GetType())
							{
							// If player collides with kamikazi, then kamikazi explodes, killing both
							case ENEMYTYPE::KAMIKAZE:
							{
								player->TakeDamage(1);
								enemy->bDestroy = true;
								AudioManager::PlayAudioSource("EnemyDeath");

								// Give player invincibility after enemy collision
								player->m_bInvincible = true;
								break;
							}
							// If player collides with warrior, then player dies, but warrior keeps going
							case ENEMYTYPE::WARRIOR:
							{
								if (player->GetCollisionBox()->GetCollider().getPosition().y - player->GetCollisionBox()->GetCollider().getSize().y / 2
									>= enemy->GetCollisionBox()->GetCollider().getPosition().y - 1)
								{
									player->SetPosition({ player->GetPosition().x,
										enemy->GetCollisionBox()->GetCollider().getPosition().y + (enemy->GetCollisionBox()->GetCollider().getSize().y / 2) +
										(Statics::fBackgroundScrollSpeed * Statics::fDeltaTime) + 2 });

									player->SetRestrictYPosition(false);
									player->SetStopInput(true);

								if (!(AudioManager::GetAudioSourceStatus("Warrior") == sf::SoundSource::Status::Playing)) {
									AudioManager::PlayAudioSource("Warrior");
								}
								}
								else
								{
									
								}
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

int EnemyManager::GetShamanCount()
{
	return m_iShamanCount;
}

int EnemyManager::GetWarriorCount()
{
	return m_iWarriorCount;
}

int EnemyManager::GetArcherCount()
{
	return m_iArcherCount;
}

int EnemyManager::GetKamikazeCount()
{
	return m_iKamikazeCount;
}

void EnemyManager::SpawnEnemies(float _rate)
{
	m_fSpawnTimer -= Statics::fDeltaTime;
	float elapsedTime = LevelLoader::GetElaspedTime();
	if (m_fSpawnTimer <= 0)
	{
		srand((unsigned)Statics::Time.getElapsedTime().asSeconds());
		m_fSpawnTimer = _rate;

		int iRandomEnemy = rand() % 4;
		if (elapsedTime > 90.0f && m_iShamanCount < 3)
		{
			// Create Shaman
			if (iRandomEnemy == 3)
			{
				m_iShamanCount++;
				CreateEnemy(
					{
						nullptr, // Set SHAMAN running sprite
						{100.0f + (rand() % 600), 0}, // Set random starting position
						{ENEMYTYPE::SHAMAN}, // Set enemy type - Shaman
						{0.8f,0.8f}, // Shaman sprite size
						{1.0f,1.0f}, // Shaman jump sprite size
						{150.0f}, // Shaman run speed
						{250.0f}, // Shaman jump speed
						{3}, // Shaman health
						{50} // Points received on shamans death
					});
			}
		}
		if (elapsedTime > 60.0f && m_iWarriorCount < 20)
		{
			// Create Warrior
			if (iRandomEnemy == 2)
			{
				m_iWarriorCount++;
				int randomIndex = rand() % PlayerManager::GetInstance().GetPlayers().size();
				float randomX = PlayerManager::GetInstance().GetPlayerFromIndex(randomIndex)->GetPosition().x;
				CreateEnemy(
					{
						nullptr, // Set warrior running sprite
						{randomX, 0}, // Set random starting position
						{ENEMYTYPE::WARRIOR}, // Set enemy type - Warrior
						{2.0f,2.0f}, // Warrior sprite size
						{0.0f,0.0f}, // Warrior does not jump
						{300.0f}, // Faster run speed
						{0.0f}, // Warrior does not jump
						{7}, // High health compared to other enemies
						{100} // Points received on warrior death - higher points due to hard to kill
					});
			}
		}
		if (elapsedTime > 30.0f && m_iArcherCount < 3)
		{
			// Create Archer
			if (iRandomEnemy == 1)
			{
				m_iArcherCount++;
				CreateEnemy(
					{
						nullptr, // Set archer running sprite
						{100.0f + (rand() % 600), 0}, // Set random starting position
						{ENEMYTYPE::ARCHER}, // Set enemy type - Archer
						{2.0f,2.0f}, // Archer sprite size
						{2.4f,2.4f}, // Archer jump sprite size
						{150.0f}, // Archer run speed
						{250.0f}, // Archer jump speed
						{4}, // Archer health
						{40} // Points received on archer death
					});
			}
		}
		if (elapsedTime > 5.0f && m_iKamikazeCount < 20)
		{
			m_iKamikazeCount++;
			CreateEnemy(
				{
					nullptr, // Set kamikaze running sprite
					{100.0f + (rand() % 600), 0}, // Set random starting position
					{ENEMYTYPE::KAMIKAZE}, // Set enemy type - Kamikaze
					{2.0f,2.0f}, // Kamikaze sprite size
					{2.4f,2.4f}, // Kamikaze jump sprite size
				});
		}
	}
}