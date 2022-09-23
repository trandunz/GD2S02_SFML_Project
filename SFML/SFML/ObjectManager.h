// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : ObjectManager.h 
// Description : ObjectManager Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class Obstacle;
class ObjectManager : public sf::Drawable
{
public:
	static ObjectManager& GetInstance();
	
	/// <summary>
	/// Force cleanup all obstacles
	/// </summary>
	void CleanupObstacles();
	/// <summary>
	/// Create an obstacle with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreateObstacle(ObstacleProperties _properties);

	/// <summary>
	/// Update all obstacles
	/// </summary>
	void Update();

	/// <summary>
	/// Handles the spawning of obstacles at a specified rate
	/// </summary>
	/// <param name="_rate"></param>
	void SpawnObstacles(float _rate);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	inline ObjectManager() {}
	inline ObjectManager(const ObjectManager&) {}
	inline ~ObjectManager() {}

	float m_SpawnTimer{ 3.0f };
	std::vector<Obstacle*> Obstacles{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	std::vector<sf::Sprite> GetObstacleSprites() const;
	std::vector<Obstacle*> GetObstacles() const;
};

