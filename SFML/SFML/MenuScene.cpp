#include "MenuScene.h"
#include "LevelLoader.h"
#include "GUI.h"
#include "GameScene.h"
#include "Math.h"

MenuScene::MenuScene()
{
	sf::Vector2f windowSize(Statics::RenderWindow.getSize());

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

	GUI::GetInstance().CreateButton("Options",
		{
			"",
			{windowSize.x / 2.0f, (windowSize.y / 1.6f)},
			nullptr,
			& TextureLoader::LoadTexture("OptionsButton.png")
		}
	);

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

	m_iButtonSelected = 3;
	GUI::GetInstance().CreateImage("Title",
		{
			&TextureLoader::LoadTexture("Title.png"),
			{windowSize.x / 2.0f, (windowSize.y / 4.0f)},
			{1.5f, 1.5f}
		});
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
			m_iButtonSelected = ++m_iButtonSelected % 4;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::S ||
			Statics::EventHandle.key.code == sf::Keyboard::Down)
		{
			m_iButtonSelected = --m_iButtonSelected % 4;
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = 3;
			}
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
			switch (m_iButtonSelected)
			{
			case 0:
			{
				button = GUI::GetInstance().GetButton("Quit");
				if (button)
					button->CallOnPress();
				break;
			}
			case 1:
			{
				button = GUI::GetInstance().GetButton("Options");
				if (button)
					button->CallOnPress();
				break;
			}
			case 2:
			{
				button = GUI::GetInstance().GetButton("High Score");
				if (button)
					button->CallOnPress();
				break;
			}
			case 3:
			{
				button = GUI::GetInstance().GetButton("Start");
				if (button)
					button->CallOnPress();
				break;
			}
			}
		}
	}
	else
		GUI::GetInstance().HandleEvents();
}

void MenuScene::Update()
{
	GUI::GetInstance().Update();
	GUI::GetInstance().ResetAllButtonsScale();

	std::string selectedButton;
	switch (m_iButtonSelected)
	{
	case 0:
	{
		selectedButton = "Quit";
		break;
	}
	case 1:
	{
		selectedButton = "High Score";
		break;
	}
	case 2:
	{
		selectedButton = "Options";
		break;
	}
	case 3:
	{
		selectedButton = "Start";
		break;
	}
	}

	ScaleSelectedButton(selectedButton);
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
		button->SetScale({ throb,throb });
	}
}
