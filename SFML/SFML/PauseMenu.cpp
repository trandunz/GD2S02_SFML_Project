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
#include "Math.h"
#include "AudioManager.h"

PauseMenu::PauseMenu()
{
	CreateMenuBackground();
	CreateMenuText();
	CreateMenuButtons();

	Statics::SetPaused(true);
	m_iButtonSelected = 0;
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
	GUI::GetInstance().ResetAllButtonsScale();

	if (m_SettingsMenu)
	{
		CleanupElements();
		m_SettingsMenu->HandleEvents();
		ScaleSelectedButton(m_SettingsMenu->GetAudioTypeButton());

		if (m_SettingsMenu->bDestroy)
		{
			delete m_SettingsMenu;
			m_SettingsMenu = nullptr;

			CreateMenuBackground();
			CreateMenuText();
			CreateMenuButtons();
		}
	}
	else {
		ScaleSelectedButton(m_vecButtons[m_iButtonSelected]);
		HandleEvents();
	}
}

void PauseMenu::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::KeyPressed && m_bButtonReleased)
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::W ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Up)
		{
			m_iButtonSelected = --m_iButtonSelected % m_vecButtons.size();
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = m_vecButtons.size() - 1;
			}
			m_bPlayMenuMove = true;
			m_bButtonReleased = false;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::S ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Down)
		{
			m_iButtonSelected = ++m_iButtonSelected % m_vecButtons.size();
			m_bPlayMenuMove = true;
			m_bButtonReleased = false;

		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Enter ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1)
		{
			Button* button = nullptr;

			button = GUI::GetInstance().GetButton(m_vecButtons[m_iButtonSelected]);
			if (button)
				button->CallOnPress();
			m_bButtonReleased = false;
		}
	}
	if (m_bPlayMenuMove)
	{
		m_bPlayMenuMove = false;
		AudioManager::PlayAudioSource("MenuMove");
	}

	if (Statics::EventHandle.type == sf::Event::KeyReleased)
	{
		m_bButtonReleased = true;
	}
}

void PauseMenu::ScaleSelectedButton(std::string _button)
{
	Button* button = GUI::GetInstance().GetButton(_button);

	if (button)
	{
		float throb = 1 + sinf(ToRad((float)Statics::Time.getElapsedTime().asMilliseconds())) / 10;
		button->SetScale({ throb, throb });
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
	m_vecButtons.emplace_back("Resume");
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
	m_vecButtons.emplace_back("Settings");
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
	m_vecButtons.emplace_back("Quit");
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

