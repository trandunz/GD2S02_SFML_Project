#include "ObjectManager.h"
#include "Obstacle.h"
#include "TextureLoader.h"
#include "Helper.h"

void ObjectManager::CleanupObstacles()
{
	CleanupVector(Obstacles);
}

void ObjectManager::CreateObstacle(ObstacleProperties _properties)
{
	Obstacles.emplace_back(new Obstacle(_properties));
}

void ObjectManager::Update()
{
	SpawnObstacles(1.5f);
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
	m_SpawnTimer -= Statics::fDeltaTime;
	if (m_SpawnTimer <= 0)
	{
		m_SpawnTimer = _rate;

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