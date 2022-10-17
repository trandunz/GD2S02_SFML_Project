// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : EndGameMenu.cpp 
// Description : EndGameMenu Implementation File		
// Author : 

#include "EndGameMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"
#include "Helper.h"

EndGameMenu::EndGameMenu()
{
	CreateMenuBackground();
	CreateMenuButtons();
	CreateMenuText();

	Statics::SetPaused(true);
}

EndGameMenu::~EndGameMenu()
{
	CleanupElements();
	Statics::SetPaused(false);
}

void EndGameMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("EndGameDullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Texture
			ScreenCentre // Position
		});
}

void EndGameMenu::CreateMenuButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("GotoHighscore", // Key
		{
			"Highscores", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 200}, // Position
			[this]()
			{
				LevelLoader::LoadLevel(LEVELS::HIGHSCORESCENE); // On Press Lambda
			},
			nullptr,
			{1.0f,1.0f}, // Scale
		});
}

void EndGameMenu::CreateMenuText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateText("FinalScoreText",
		{
			ScreenCentre,
			"Score: " + FloatToString(Statics::fGameScore, 0),
			{92, 92, 92},
			128,
			sf::Color::White
		});
}

void EndGameMenu::CleanupElements()
{
	GUI::GetInstance().CleanupImageElement("EndGameDullBackground");
	GUI::GetInstance().CleanupTextElement("FinalScoreText");
	GUI::GetInstance().CleanupButtonElement("GotoHighscore");
}
