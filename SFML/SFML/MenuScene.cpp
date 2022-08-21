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
			{windowSize.x / 2.0f, windowSize.y / 2.0f},
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
			{windowSize.x / 2.0f, (windowSize.y / 1.5f)},
			nullptr,
			& TextureLoader::LoadTexture("OptionsButton.png")
		}
	);

	GUI::GetInstance().CreateButton("Quit",
		{
			"",
			{windowSize.x / 2.0f, (windowSize.y / 1.2f)},
			[]()
			{
				Statics::RenderWindow.close();
			},
			&TextureLoader::LoadTexture("QuitButton.png")
		}
	);

	m_iButtonSelected = 2;
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
		if (Statics::EventHandle.key.code == sf::Keyboard::W)
		{
			m_iButtonSelected = ++m_iButtonSelected % 3;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::S)
		{
			m_iButtonSelected = --m_iButtonSelected % 3;
			if (m_iButtonSelected < 0)
			{
				m_iButtonSelected = 2;
			}
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Enter)
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
		selectedButton = "Options";
		break;
	}
	case 2:
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
		float throb = 1 + sinf(ToRad(Statics::Time.getElapsedTime().asMilliseconds())) / 10;
		button->SetScale({ throb,throb });
	}
}
