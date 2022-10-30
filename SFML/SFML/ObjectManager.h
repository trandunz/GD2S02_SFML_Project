// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : ObjectManager.h 
// Description : ObjectManager Header File
// Author : Inman, Will; Frear, Stace

#pragma once
#include "Statics.h"

class Pickup;
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
	/// Force cleanup all pickups
	/// </summary>
	void CleanupPickups();

	/// <summary>
	/// Cleans up all objects that are marked for destroy
	/// </summary>
	void CleanupDestroyed();

	/// <summary>
	/// Force clean up everything including obstacles
	/// </summary>
	void CleanupEverything();

	/// <summary>
	/// Create an obstacle with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreateObstacle(ObstacleProperties _properties);

	/// <summary>
	/// Create a pickup with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreatePickup(PickupProperties _properties);

	/// <summary>
	/// Update all obstacles
	/// </summary>
	void Update();

	/// <summary>
	/// Handles the spawning of obstacles at a specified rate
	/// </summary>
	/// <param name="_rate"></param>
	void SpawnObstacles(float _rate);

	/// <summary>
	/// Handles the spawning of pickups at a specified rate
	/// </summary>
	/// <param name="_rate"></param>
	void SpawnPickups(float _rate);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	inline ObjectManager() {}
	inline ObjectManager(const ObjectManager&) {}
	inline ~ObjectManager() {}

	float m_ObstacleSpawnTimer{ 3.0f };
	float m_PickupSpawnTimer{ 8.0f };
	std::vector<Obstacle*> m_vecObstacles{};
	std::vector<Pickup*> m_vecPickups{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	std::vector<sf::Sprite> GetObstacleSprites();
	std::vector<Obstacle*>& GetObstacles();
	std::vector<Pickup*>& GetPickups();
};

