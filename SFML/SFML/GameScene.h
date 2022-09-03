#pragma once
#include "Level.h"
#include "Statics.h"

class GameScene : public Level
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void CreateScrollingBackground();
	void ScrollBackground(float _speed);

	std::vector<sf::Sprite> m_Backgrounds{};
	float m_fDistanceTravelled{};
};

