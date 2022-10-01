#include "SettingsMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"

SettingsMenu::SettingsMenu()
{
	CreateMenuBackground();
	CreateMenuText();
	CreateMenuButtons();
}

SettingsMenu::~SettingsMenu()
{
	CleanupElements();
}

void SettingsMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("SettingsMenuDullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Texture
			ScreenCentre // Position
		});

	GUI::GetInstance().CreateImage("SettingsMenuBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			ScreenCentre // Position
		});
}

void SettingsMenu::CreateMenuButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Back", // Key
		{
			"Back", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 80}, // Position
			[this]()
			{
				bDestroy = true; // On Press Lambda
			},
			nullptr,
			{1,1}, // Scale
		});
}

void SettingsMenu::CreateMenuText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("SettingsMenuTitle", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 110}, // Position
			"Settings" // Label / String
		});
}

void SettingsMenu::CleanupElements()
{
	GUI::GetInstance().CleanupImageElement("SettingsMenuBackground");
	GUI::GetInstance().CleanupImageElement("SettingsMenuDullBackground");
	GUI::GetInstance().CleanupTextElement("SettingsMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Back");
}
