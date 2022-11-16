// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : MenuScene.cpp 
// Description : MenuScene Implementation File		
// Author : Bartlett, Benjamin

#include "MenuScene.h"
#include "LevelLoader.h"
#include "GUI.h"
#include "GameScene.h"
#include "Math.h"
#include "TextureLoader.h"
#include "SettingsMenu.h"
#include "AudioManager.h"

MenuScene::MenuScene()
{
	CreateElements();

	m_iButtonSelected = 0;
}

MenuScene::~MenuScene()
{
	GUI::GetInstance().CleanupElements();
	if (m_SettingsMenu)
	{
		delete m_SettingsMenu;
		m_SettingsMenu = nullptr;
	}
}

void MenuScene::HandleEvents()
{
	bool playMenuMove = false;
	if (Statics::EventHandle.type == sf::Event::KeyPressed) 
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Escape)
		{
			Statics::RenderWindow.close();
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::W ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Up)
		{
			m_iButtonSelected = --m_iButtonSelected % m_vecButtons.size();
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = m_vecButtons.size() - 1;
			}
			playMenuMove = true;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::S ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Down)
		{
			m_iButtonSelected = ++m_iButtonSelected % m_vecButtons.size();
			playMenuMove = true;

		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Enter ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::B ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::N ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1 ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad2 ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad3)
		{
			Button* button = nullptr;

			button = GUI::GetInstance().GetButton(m_vecButtons[m_iButtonSelected]);
			if (button)
				button->CallOnPress();
		}
	}
	else
		GUI::GetInstance().HandleEvents();

	if (playMenuMove)
	{
		playMenuMove = false;
		AudioManager::PlayAudioSource("MenuMove");
	}
}

void MenuScene::Update()
{
	GUI::GetInstance().Update();
	GUI::GetInstance().ResetAllButtonsScale();

	ScaleSelectedButton(m_vecButtons[m_iButtonSelected]);

	if (m_SettingsMenu)
	{
		CleanupElements();

		if (m_SettingsMenu->bDestroy)
		{
			delete m_SettingsMenu;
			m_SettingsMenu = nullptr;

			CreateElements();
		}
	}
}

void MenuScene::Draw()
{
	Statics::RenderWindow.draw(GUI::GetInstance());
}

void MenuScene::ScaleSelectedButton(std::string _button)
{
	Button* button = GUI::GetInstance().GetButton(_button);

	if (button)
	{
		float throb = 1 + sinf(ToRad((float)Statics::Time.getElapsedTime().asMilliseconds())) / 10;
		button->SetScale({ throb, throb });
	}
}

void MenuScene::CleanupElements()
{
	GUI::GetInstance().CleanupButtonElement("Quit");
	GUI::GetInstance().CleanupButtonElement("High Score");
	GUI::GetInstance().CleanupButtonElement("Options");
	GUI::GetInstance().CleanupButtonElement("Start");
	GUI::GetInstance().CleanupImageElement("Title");
}

void MenuScene::CreateElements()
{
	sf::Vector2f windowSize(Statics::RenderWindow.getSize());

	m_vecButtons.emplace_back("Start");
	GUI::GetInstance().CreateButton("Start",
		{
			"",
			{windowSize.x / 2.0f, windowSize.y / 2.1f},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::CHARACTERSELECTSCENE);
			},
			&TextureLoader::LoadTexture("StartButton.png")
		}
	);

	m_vecButtons.emplace_back("Options");
	GUI::GetInstance().CreateButton("Options",
		{
			"",
			{windowSize.x / 2.0f, (windowSize.y / 1.6f)},
			[this]()
			{
				m_SettingsMenu = new SettingsMenu;
			},
			&TextureLoader::LoadTexture("OptionsButton.png")
		}
	);

	m_vecButtons.emplace_back("High Score");
	GUI::GetInstance().CreateButton("High Score",
		{
			"",
			{ windowSize.x / 2.0f, (windowSize.y / 1.3f) },
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::HIGHSCORE);
			},
			&TextureLoader::LoadTexture("HighScoreButton.png")
		}
	);

	m_vecButtons.emplace_back("Quit");
	GUI::GetInstance().CreateButton("Quit",
		{
			"",
			{windowSize.x / 2.0f, (windowSize.y / 1.1f)},
			[]()
			{
				Statics::RenderWindow.close();
			},
			&TextureLoader::LoadTexture("QuitButton.png")
		}
	);

	GUI::GetInstance().CreateImage("Title",
		{
			&TextureLoader::LoadTexture("Title.png"),
			{windowSize.x / 2.0f, (windowSize.y / 4.0f)},
			{1.5f, 1.5f}
		});

	GUI::GetInstance().CreateImage("Logo",
		{
			&TextureLoader::LoadTexture("Logo.png"),
			{(windowSize.x - 40.0f), (windowSize.y - 38.4f)},
			{0.2f, 0.2f}
		});

	// SFX
	AudioManager::CreateAudioSource("MenuMove", "menu_move.wav");
	AudioManager::CreateAudioSource("Abracadabros", "Abracadabrooooos.wav");
	AudioManager::PlayAudioSource("Abracadabros");
	AudioManager::StopMusic();

}
