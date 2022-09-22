#include "ProjectileManager.h"
#include "Projectile.h"
#include "ObjectManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Helper.h"
#include "Obstacle.h"

void ProjectileManager::CleanupDestroyed()
{
	auto it = m_Projectiles.begin();
	while (it != m_Projectiles.end())
	{
		if ((*it)->Destroy == true)
		{
			if ((*it) != nullptr)
			{
				delete (*it);
				(*it) = nullptr;
			}
			it = m_Projectiles.erase(it);
			continue;
		}
		it++;
	}
}

void ProjectileManager::CleanupProjectiles()
{
	CleanupVector(m_Projectiles);
}

void ProjectileManager::CreateProjectile(ProjectileProperties _properties)
{
	m_Projectiles.emplace_back(new Projectile(_properties));
}

void ProjectileManager::Update()
{
	sf::Vector2f pos{};
	sf::Vector2u screenSize = Statics::RenderWindow.getSize();

	for (auto& projectile : m_Projectiles)
	{
		pos = projectile->GetPosition();
		if (pos.x < 0
			|| pos.x > screenSize.x
			|| pos.y < 0
			|| pos.y > screenSize.y)
		{
			projectile->Destroy = true;
		}
		else
		{
			for (auto& obstacle : ObjectManager::GetInstance().GetObstacles())
			{
				if (projectile->CheckCollision(*obstacle->GetCollisionBox()))
				{
					projectile->Destroy = true;
					break;
				}
			}
			if (projectile->IsFriendly() == true)
			{
				for (auto& enemy : EnemyManager::GetInstance().GetEnemies())
				{
					if (enemy != nullptr)
					{
						if (projectile->CheckCollision(*enemy->GetCollider()))
						{
							enemy->TakeDamage(projectile->GetDamagedDealt());
							//Assume that if it is not marked to be destroyed
							//then it is a secondary attack projectile that dealt
							//no damage but will inflict debuffs
							if(projectile->IsDestroyedOnCollision())
							{
								projectile->Destroy = true;
							}
							else
							{
								ELEMENTTYPE projElement = projectile->GetElement();
								switch (projElement)
								{
								case ELEMENTTYPE::NONE:
								{
									Print("WARN: Secondary projectile has no element");
									break;
								}
								case ELEMENTTYPE::FIRE:
								{
									enemy->DamageEnemyOverTime(DEBUFF_BURNAMOUNT, DEBUFF_BURNTIME);
									break;
								}
								case ELEMENTTYPE::WATER:
								{
									enemy->SlowEnemy(DEBUFF_SLOWTIME, DEBUFF_SLOWAMOUNT);
									break;
								}
								case ELEMENTTYPE::EARTH:
								{
									enemy->FreezeEnemy(DEBUFF_FREEZETIME);
									break;
								}
								default:
									break;
								}
							}
							break;
						}
					}
				}
			}

			if (projectile->IsFriendly() == false)
			{
				for (auto& player : PlayerManager::GetInstance().GetPlayers())
				{
					if (player != nullptr)
					{
						if (projectile->CheckCollision(*player->GetCollisionBox()))
						{
							player->TakeDamage( projectile->GetDamagedDealt() );
							if (projectile->IsDestroyedOnCollision())
							{
								projectile->Destroy = true;
							}
							break;
						}
					}
				}
			}
		}

		projectile->Update();
	}
}

void ProjectileManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& projectile : m_Projectiles)
	{
		_target.draw(*projectile);
	}
}
