// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : PauseMenu.cpp 
// Description : PauseMenu Implementation File		
// Author : 

#include "PauseMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"
#include "SettingsMenu.h"

PauseMenu::PauseMenu()
{
	CreateMenuBackground();
	CreateMenuText();
	CreateMenuButtons();

	Statics::SetPaused(true);
}

PauseMenu::~PauseMenu()
{
	Statics::SetPaused(false);

	CleanupElements();

	if (m_SettingsMenu)
	{
		delete m_SettingsMenu;
		m_SettingsMenu = nullptr;
	}
}

void PauseMenu::Update()
{
	if (m_SettingsMenu)
	{
		CleanupElements();

		if (m_SettingsMenu->bDestroy)
		{
			delete m_SettingsMenu;
			m_SettingsMenu = nullptr;

			CreateMenuBackground();
			CreateMenuText();
			CreateMenuButtons();
		}
	}
}

void PauseMenu::CreateMenuBackground()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateImage("PauseMenuDullBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/DullBackground.png"), // Texture
			ScreenCentre // Position
		});

	GUI::GetInstance().CreateImage("Background", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			ScreenCentre, // Position
			{0.3f, 0.3f}
		});
}

void PauseMenu::CreateMenuButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Resume", // Key
		{
			"", // Label / String
			{ ScreenCentre.x,ScreenCentre.y - 40}, // Position
			[this]()
			{
				bDestroy = true; // On Press Lambda
			},
			& TextureLoader::LoadTexture("GUI/Resume.png"),
			{0.9f,0.9f}, // Scale
		});
	GUI::GetInstance().CreateButton("Settings", // Key
		{
			"", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 20}, // Position
			[this]()
			{
				m_SettingsMenu = new SettingsMenu; // On Press Lambda
			},
			& TextureLoader::LoadTexture("GUI/Settings.png"),
			{0.9f,0.9f}, // Scale
		});
	GUI::GetInstance().CreateButton("Quit", // Key
		{
			"", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 80}, // Position
			[this]()
			{
				LevelLoader::LoadLevel(LEVELS::MENUSCENE); // On Press Lambda
			},
			& TextureLoader::LoadTexture("GUI/Quit.png"),
			{0.9f,0.9f}, // Scale
		});
}

void PauseMenu::CreateMenuText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("PauseMenuTitle", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 100}, // Position
			"Paused" // Label / String
		});
}

void PauseMenu::CleanupElements()
{
	GUI::GetInstance().CleanupImageElement("Background");
	GUI::GetInstance().CleanupImageElement("PauseMenuDullBackground");
	GUI::GetInstance().CleanupTextElement("PauseMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Resume");
	GUI::GetInstance().CleanupButtonElement("Settings");
	GUI::GetInstance().CleanupButtonElement("Quit");
}
