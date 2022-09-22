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

	void CleanupDestroyed();
	void CleanupProjectiles();
	void CreateProjectile(ProjectileProperties _properties);
	void Update();

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	inline ProjectileManager() {}
	inline ProjectileManager(const ProjectileManager&) {};
	inline ~ProjectileManager() {}

	void ApplyDebuff_Enemy(Enemy* _target, ELEMENTTYPE _element);

	std::vector<Projectile*> m_Projectiles{};
};