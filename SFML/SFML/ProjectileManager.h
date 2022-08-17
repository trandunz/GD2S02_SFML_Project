#pragma once
#include "Statics.h"

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

	std::vector<Projectile*> m_Projectiles;
};

