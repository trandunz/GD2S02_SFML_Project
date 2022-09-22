// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : EnemyManager.h 
// Description : EnemyManager Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class Enemy;
class EnemyManager : public sf::Drawable
{
public:
	inline static EnemyManager& GetInstance()
	{
		static EnemyManager instance;
		return instance;
	}

	void CleanupDestroyed();
	void CleanupEnemies();
	void CreateEnemy(EnemyProperties _properties);
	void Update();

	void SpawnEnemies(float _rate);

	std::vector<sf::Sprite> GetEnemySprites() const ;
	std::vector<Enemy*>& GetEnemies();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline EnemyManager() {}
	inline EnemyManager(const EnemyManager&) {}
	inline ~EnemyManager() {}

	float m_fSpawnTimer{1.0f}; // Timer for spawning enemies
	std::vector<Enemy*> m_Enemies{}; // Vector to hold all enemy types

	float m_fDestroyDistanceY{ 64.0f }; // The distance below the game window of when to destroy enemies
};

