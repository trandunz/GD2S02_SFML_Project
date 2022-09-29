#include "PauseMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"

PauseMenu::PauseMenu()
{
	CreateMenuBackground();
	CreateMenuText();
	CreateMenuButtons();

	Statics::SetPaused(true);
}

PauseMenu::~PauseMenu()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("DullBackground");
	GUI::GetInstance().CleanupTextElement("PauseMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Quit");
}

void PauseMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("DullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Texture
			ScreenCentre // Position
		});

	GUI::GetInstance().CreateImage("Background", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			ScreenCentre // Position
		});
}

void PauseMenu::CreateMenuButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Quit", // Key
		{
			"Quit", // Label / String
			{ ScreenCentre.x,ScreenCentre.y}, // Position
			[this]()
			{	
				Statics::SetPaused(false); // On Press Lambda
				bDestroy = true;
			},
			nullptr,
			{1,1}, // Scale
		});
}

void PauseMenu::CreateMenuText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("PauseMenuTitle", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 80}, // Position
			"Paused" // Label / String
		});
}
