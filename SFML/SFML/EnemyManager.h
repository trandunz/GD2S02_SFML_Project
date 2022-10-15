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
	static EnemyManager& GetInstance();

	/// <summary>
	/// Cleans up any enemies with bDestory = true
	/// </summary>
	void CleanupDestroyed();

	/// <summary>
	/// Force cleans up all enemies
	/// </summary>
	void CleanupEnemies();

	/// <summary>
	/// Creates an eenemy with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreateEnemy(EnemyProperties _properties);

	/// <summary>
	/// Handles updating all enemies
	/// </summary>
	void Update();

	/// <summary>
	/// Handles the spawning of enemies at the specified rate
	/// </summary>
	/// <param name="_rate"></param>
	void SpawnEnemies(float _rate);

private:
	/// <summary>
	/// Drawing of enemies to window
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_states"></param>
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline EnemyManager() {}
	inline EnemyManager(const EnemyManager&) {}
	inline ~EnemyManager() {}

	float m_fSpawnTimer{1.0f}; // Timer for spawning enemies
	std::vector<Enemy*> m_Enemies{}; // Vector to hold all enemy types

	float m_fDestroyDistanceY{ 64.0f }; // The distance below the game window of when to destroy enemies

	int m_iShamanCount{};
	int m_iWarriorCount{};
	int m_iArcherCount{};
	int m_iKamikazeCount{};
public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	std::vector<sf::Sprite> GetEnemySprites() const;
	std::vector<Enemy*>& GetEnemies();

	int GetShamanCount();
	int GetWarriorCount();
	int GetArcherCount();
	int GetKamikazeCount();
};

