#include "ObjectManager.h"
#include "Obstacle.h"

#include <iostream>

void ObjectManager::CleanupObstacles()
{
	for (auto& obstacle : Obstacles)
	{
		if (obstacle != nullptr)
		{
			delete obstacle;
			obstacle = nullptr;
		}
	}
	Obstacles.clear();
	Obstacles.resize(0);
}

void ObjectManager::CreateObstacle(ObstacleProperties _properties)
{
	Obstacles.emplace_back(new Obstacle(_properties));
}

void ObjectManager::Update()
{
	SpawnObstacles(0.8f);
	auto it = Obstacles.begin();
	while (it != Obstacles.end())
	{
		(*it)->Update();
		++it;
	}
}

std::vector<sf::Sprite> ObjectManager::GetObstacleSprites() const
{
	std::vector<sf::Sprite> sprites{};
	for (auto& object : Obstacles)
	{
		sprites.emplace_back(object->GetSprite());
	}
	return sprites;
}

std::vector<Obstacle*> ObjectManager::GetObstacles() const
{
	return Obstacles;
}

void ObjectManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& object : Obstacles)
	{
		_target.draw(*object);
	}
}

void ObjectManager::SpawnObstacles(float _rate)
{
	m_SpawnTimer -= Statics::DeltaTime;
	if (m_SpawnTimer <= 0)
	{
		m_SpawnTimer = _rate;

		int iRandomNum = rand() % 4;
		if (iRandomNum == 0)
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("rock_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2}
				});
		}
		else if (iRandomNum == 1)
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("hedge_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2}
				});
		}
		else if (iRandomNum == 2)
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("log_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2}
				});
		}
		else
		{
			CreateObstacle(
				{
					&TextureLoader::LoadTexture("tree_obstacle.png"),
					{100.0f + (rand() % 600), -32.0f},
					{2,2}
				});
		}
	}
}