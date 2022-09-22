#pragma once
#include "Statics.h"


#define DEBUFF_FREEZETIME 1.5f
#define DEBUFF_SLOWTIME 1.5f
#define DEBUFF_SLOWAMOUNT 0.5f
#define DEBUFF_BURNTIME 2.0f
#define DEBUFF_BURNAMOUNT 1

class Projectile;
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

	std::vector<Projectile*> m_Projectiles{};
};