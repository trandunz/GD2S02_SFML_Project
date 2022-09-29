// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : GameScene.h 
// Description : GameScene Header File
// Author : Inman, Will

#pragma once
#include "Level.h"
#include "Statics.h"
#include "PauseMenu.h"

class PauseMenu;
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
	void ScrollBackground();

	std::vector<sf::Sprite> m_Backgrounds{};
	float m_fDistanceTravelled{};

	PauseMenu* m_PauseMenu{ nullptr };
public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

