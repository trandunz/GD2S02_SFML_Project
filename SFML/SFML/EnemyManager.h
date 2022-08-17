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

	float m_SpawnTimer{1.0f};
	std::vector<Enemy*> m_Enemies{};
};

