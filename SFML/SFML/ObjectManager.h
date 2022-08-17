#pragma once
#include "Statics.h"

class Obstacle;
class ObjectManager : public sf::Drawable
{
public:
	inline static ObjectManager& GetInstance()
	{
		static ObjectManager instance;
		return instance;
	}

	void CleanupObstacles();
	void CreateObstacle(ObstacleProperties _properties);
	void Update();
	std::vector<sf::Sprite> GetObstacleSprites() const;
	std::vector<Obstacle*> GetObstacles() const;

	void SpawnObstacles(float _rate);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	inline ObjectManager() {}
	inline ObjectManager(const ObjectManager&) {}
	inline ~ObjectManager() {}

	float m_SpawnTimer{ 3.0f };
	std::vector<Obstacle*> Obstacles;
};

