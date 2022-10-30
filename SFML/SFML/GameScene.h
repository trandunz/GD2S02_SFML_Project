// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : GameScene.h 
// Description : GameScene Header File
// Author : Inman, Will; Frear, Stace

#pragma once
#include "Level.h"
#include "Statics.h"
#include "PauseMenu.h"

class PauseMenu;
class EndGameMenu;
class GameScene : public Level
{
public:
	/// <summary>
	/// GameScene Constructor
	/// </summary>
	GameScene();
	/// <summary>
	/// GameScene Destructor
	/// </summary>
	virtual ~GameScene();

	/// <summary>
	/// Handles all events like keys and mouse
	/// </summary>
	virtual void HandleEvents() override;
	/// <summary>
	/// Update all objects
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// Draw all objects
	/// </summary>
	virtual void Draw() override;

private:
	/// <summary>
	/// Create the scrolling background
	/// </summary>
	void CreateScrollingBackground();
	/// <summary>
	/// Scroll the background
	/// </summary>
	void ScrollBackground();
	/// <summary>
	/// Cleanup the pause menu if its marked for destroy
	/// </summary>
	void CleanupPauseMenuIfDestroyed();

	std::vector<sf::Sprite> m_vecBackgrounds{};
	float m_fDistanceTravelled{};
	bool m_bGameOver{ false };

	PauseMenu* m_PauseMenu{ nullptr };
	EndGameMenu* m_EndGameMenu{ nullptr };
public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

