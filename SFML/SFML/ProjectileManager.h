// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : ProjectileManager.h 
// Description : ProjectileManager Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

constexpr float DEBUFF_FREEZETIME	{ 1.5f };
constexpr float DEBUFF_SLOWTIME		{ 1.5f };
constexpr float DEBUFF_SLOWAMOUNT	{ 0.5f };
constexpr float DEBUFF_BURNTIME		{ 2.0f };
constexpr unsigned DEBUFF_BURNAMOUNT{ 1 };

class Player;
class Projectile;
class Enemy;
class ProjectileManager : public sf::Drawable
{
public:
	inline static ProjectileManager& GetInstance()
	{
		static ProjectileManager instance;
		return instance;
	}

	/// <summary>
	/// Cleans up any projectiles marked for destroy
	/// </summary>
	void CleanupDestroyed();
	/// <summary>
	/// Force cleans up all projectiles
	/// </summary>
	void CleanupProjectiles();
	/// <summary>
	/// Create a projectile with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreateProjectile(ProjectileProperties _properties);

	/// <summary>
	/// Update all projectiles
	/// </summary>
	void Update();

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	inline ProjectileManager() {}
	inline ProjectileManager(const ProjectileManager&) {};
	inline ~ProjectileManager() {}

	/// <summary>
	/// Apply the specified element debuff to an enemy
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_element"></param>
	void ApplyDebuff(Enemy* _target, ELEMENTTYPE _element);
	/// <summary>
	/// Apply the specified element debuff to a player
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_element"></param>
	void ApplyDebuff(Player* _target, ELEMENTTYPE _element);

	std::vector<Projectile*> m_Projectiles{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};