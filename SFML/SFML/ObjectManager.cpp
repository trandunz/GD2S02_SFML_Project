// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : ObjectManager.cpp 
// Description : ObjectManager Implementation File		
// Author : Inman, Will

#include "ObjectManager.h"
#include "Obstacle.h"
#include "TextureLoader.h"
#include "Helper.h"
#include "Pickup.h"
#include "PlayerManager.h"

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager instance;
	return instance;
}

void ObjectManager::CleanupObstacles()
{
	CleanupVector(m_vecObstacles);
}

void ObjectManager::CleanupPickups()
{
	CleanupVector(m_vecPickups);
}

void ObjectManager::CleanupDestroyed()
{
	auto it = m_vecPickups.begin();
	while (it != m_vecPickups.end())
	{
		if ((*it)->bDestroy == true)
		{
			if ((*it) != nullptr)
			{
				delete (*it);
				(*it) = nullptr;
			}
			it = m_vecPickups.erase(it);
			continue;
		}
		it++;
	}
}

void ObjectManager::CleanupEverything()
{
	CleanupObstacles();
	CleanupPickups();
}

void ObjectManager::CreateObstacle(ObstacleProperties _properties)
{
	m_vecObstacles.emplace_back(new Obstacle(_properties));
}

void ObjectManager::CreatePickup(PickupProperties _properties)
{
	m_vecPickups.emplace_back(new Pickup(_properties));
}

void ObjectManager::Update()
{
	SpawnObstacles(1.5f);
	SpawnPickups(3.0f);

	for (auto& obstacle : m_vecObstacles)
	{
		obstacle->Update();
	}

	auto& playerList = PlayerManager::GetInstance().GetPlayers();
	for (auto& pickup : m_vecPickups)
	{
		pickup->Update();
		for (auto& player : playerList)
		{
			pickup->CheckForPickup(*player);
		}
	}
}

std::vector<sf::Sprite> ObjectManager::GetObstacleSprites()
{
	std::vector<sf::Sprite> sprites{};
	for (auto& object : m_vecObstacles)
	{
		sprites.emplace_back(object->GetSprite());
	}
	return sprites;
}

std::vector<Obstacle*>& ObjectManager::GetObstacles()
{
	return m_vecObstacles;
}

std::vector<Pickup*>& ObjectManager::GetPickups()
{
	return m_vecPickups;
}

void ObjectManager::SpawnPickups(float _rate)
{
	m_PickupSpawnTimer -= Statics::fDeltaTime;
	if (m_PickupSpawnTimer <= 0)
	{
		m_PickupSpawnTimer = _rate;

		int iRandomNum = rand() % 2;
		if (iRandomNum == 1)
		{
			if (Statics::bDebugMode)
				Print("Spawned Health Pickup!");

			CreatePickup(
				{
					PICKUPTYPE::HEALTH,
					{100.0f + (rand() % 600), -32.0f},
					{0, Statics::fBackgroundScrollSpeed}
				});
		}
		else
		{
			if (Statics::bDebugMode)
				Print("Spawned Mana Pickup!");

			CreatePickup(
				{
					PICKUPTYPE::MANA,
					{100.0f + (rand() % 600), -32.0f},
					{0, Statics::fBackgroundScrollSpeed}
				});
		}
	}
}

void ObjectManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& object : m_vecObstacles)
	{
		_target.draw(*object);
	}

	for (auto& pickup : m_vecPickups)
	{
		_target.draw(*pickup);
	}
}

void ObjectManager::SpawnObstacles(float _rate)
{
	m_ObstacleSpawnTimer -= Statics::fDeltaTime;
	if (m_ObstacleSpawnTimer <= 0)
	{
		m_ObstacleSpawnTimer = _rate;

		int iRandomNum = rand() % 3;
		if (iRandomNum == 0)
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("Obstacles/rock_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2},
					{40,40},
					{6.0f}
				});
		}
		else if (iRandomNum == 1)
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("Obstacles/hedge_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2},
					{40,40},
					{6.0f}
				});
		}
		else
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("Obstacles/log_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2},
					{54,20},
					{8.0f}
				});
		}
	}
}