// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : MenuScene.cpp 
// Description : MenuScene Implementation File		
// Author :

#include "MenuScene.h"
#include "LevelLoader.h"
#include "GUI.h"
#include "GameScene.h"
#include "Math.h"
#include "TextureLoader.h"

MenuScene::MenuScene()
{
	sf::Vector2f windowSize(Statics::RenderWindow.getSize());

	m_vecButtons.emplace_back("Start");
	GUI::GetInstance().CreateButton("Start",
		{
			"",
			{windowSize.x / 2.0f, windowSize.y / 2.1f},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::GAMESCENE);
			},
			&TextureLoader::LoadTexture("StartButton.png")
		}
	);

	m_vecButtons.emplace_back("Options");
	GUI::GetInstance().CreateButton("Options",
		{
			"",
			{windowSize.x / 2.0f, (windowSize.y / 1.6f)},
			nullptr,
			& TextureLoader::LoadTexture("OptionsButton.png")
		}
	);

	m_vecButtons.emplace_back("High Score");
	GUI::GetInstance().CreateButton("High Score",
		{
			"",
			{ windowSize.x / 2.0f, (windowSize.y / 1.3f) },
			[]()
			{
				Statics::RenderWindow.close();
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

	m_iButtonSelected = 0;


}

MenuScene::~MenuScene()
{
	GUI::GetInstance().CleanupElements();
}

void MenuScene::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::KeyPressed) {
		if (Statics::EventHandle.key.code == sf::Keyboard::W ||
			Statics::EventHandle.key.code == sf::Keyboard::Up)
		{
			m_iButtonSelected = --m_iButtonSelected % m_vecButtons.size();
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = m_vecButtons.size() - 1;
			}
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::S ||
			Statics::EventHandle.key.code == sf::Keyboard::Down)
		{
			m_iButtonSelected = ++m_iButtonSelected % m_vecButtons.size();

		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Enter ||
			Statics::EventHandle.key.code == sf::Keyboard::V ||
			Statics::EventHandle.key.code == sf::Keyboard::B ||
			Statics::EventHandle.key.code == sf::Keyboard::N ||
			Statics::EventHandle.key.code == sf::Keyboard::Numpad1 ||
			Statics::EventHandle.key.code == sf::Keyboard::Numpad2 ||
			Statics::EventHandle.key.code == sf::Keyboard::Numpad3)
		{
			Button* button = nullptr;

			button = GUI::GetInstance().GetButton(m_vecButtons[m_iButtonSelected]);
			if (button)
				button->CallOnPress();
		}
	}
	else
		GUI::GetInstance().HandleEvents();
}

void MenuScene::Update()
{
	GUI::GetInstance().Update();
	GUI::GetInstance().ResetAllButtonsScale();

	ScaleSelectedButton(m_vecButtons[m_iButtonSelected]);
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
