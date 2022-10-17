// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : CharacterSelectScene.cpp 
// Description : CharacterSelectScene Implementation File		
// Author : Bartlett, Benjamin

#include "CharacterSelectScene.h"
#include "LevelLoader.h"
#include "GUI.h"
#include "Math.h"
#include "TextureLoader.h"
#include "PlayerManager.h"
#include "AudioManager.h"

CharacterSelectScene::CharacterSelectScene()
{
	sf::Vector2f windowSize(Statics::RenderWindow.getSize());
	m_sFireElement =  "Unit/Player/Fire_Mage_Static.png" ;
	m_sEarthElement = "Unit/Player/Earth_Mage_Static.png";
	m_sWaterElement = "Unit/Player/Water_Mage_Static.png";

	GUI::GetInstance().CreateButton("Start",
		{
			"",
			{windowSize.x / 2.0f, windowSize.y / 1.3f},
			[]()
			{
				LevelLoader::LoadLevel(LEVELS::GAMESCENE);
			},
			&TextureLoader::LoadTexture("StartButton.png")
		}
	);

	GUI::GetInstance().CreateImage("Fire_Mage",
		{
			&TextureLoader::LoadTexture(m_sFireElement),
			{windowSize.x / 4.0f, (windowSize.y / 3.0f)},
			{2.0f, 2.0f}
		});

	GUI::GetInstance().CreateImage("Earth_Mage",
		{
			&TextureLoader::LoadTexture(m_sEarthElement),
			{windowSize.x / 2.0f, (windowSize.y / 3.0f)},
			{2.0f, 2.0f}
		});

	GUI::GetInstance().CreateImage("Water_Mage",
		{
			&TextureLoader::LoadTexture(m_sWaterElement),
			{(windowSize.x / 4.0f) * 3.0f, (windowSize.y / 3.0f)},
			{2.0f, 2.0f}
		});

	GUI::GetInstance().CreateImage("Player1",
		{
			&TextureLoader::LoadTexture("Player1.png"),
			{(windowSize.x / 4.0f), (windowSize.y / 6.0f)},
			{0.5f, 0.5f}
		});

	GUI::GetInstance().CreateImage("Player2",
		{
			&TextureLoader::LoadTexture("Player2.png"),
			{(windowSize.x / 4.0f) * 3.0f, (windowSize.y / 6.0f)},
			{0.5f, 0.5f}
		});

	m_v2fPosition1 = { (windowSize.x / 4.0f), (windowSize.y / 6.0f) };
	m_v2fPosition2 = { (windowSize.x / 2.0f), (windowSize.y / 6.0f) };
	m_v2fPosition3 = { (windowSize.x / 4.0f) * 3.0f, (windowSize.y / 6.0f) };

	m_iPlayer1Selection = 1;
	m_iPlayer2Selection = 3;

	m_bPlayer1Selected = false;
	m_bPlayer2Selected = false;

	// Music
	AudioManager::PlayMusic("Music_Menu.wav", true);

	// SFX
	AudioManager::CreateAudioSource("MenuMove", "menu_move.wav");
	AudioManager::CreateAudioSource("MenuEnter", "menu_enter.wav");
	AudioManager::CreateAudioSource("Abracadabros", "Abracadabrooooos.wav");
	AudioManager::PlayAudioSource("MenuEnter");
}

CharacterSelectScene::~CharacterSelectScene()
{
	GUI::GetInstance().CleanupElements();
}

void CharacterSelectScene::HandleEvents()
{
	bool playMenuMove = false;
	bool playMenuEnter = false;
	if (Statics::EventHandle.type == sf::Event::KeyPressed) {

		// If both players are selected
		if (m_bPlayer1Selected && m_bPlayer2Selected)
		{
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::Enter ||
				Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
				Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1)
			{
				Button* button = nullptr;

				button = GUI::GetInstance().GetButton("Start");
				if (button)
					button->CallOnPress();
			}
		}

		// Player 1 selection
		if (!m_bPlayer1Selected)
		{
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::A)
			{
				m_iPlayer1Selection = SelectLeft(m_iPlayer1Selection);
				playMenuMove = true;
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::D)
			{
				m_iPlayer1Selection = SelectRight(m_iPlayer1Selection);
				playMenuMove = true;
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::V)
			{
				playMenuEnter = true;
				m_bPlayer1Selected = true;
				PlayerManager::GetInstance().ePlayer1Element = SetPlayerElement(m_iPlayer1Selection);
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::B)
			{
				LevelLoader::LoadLevel(LEVELS::MENUSCENE);
			}
		}
		else if (Statics::EventHandle.key.code == sf::Keyboard::Key::B)
		{
			m_bPlayer1Selected = false;
		}

		// Player 2 Selection
		if (!m_bPlayer2Selected)
		{
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::Left)
			{
				playMenuMove = true;
				m_iPlayer2Selection = SelectLeft(m_iPlayer2Selection);
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::Right)
			{
				playMenuMove = true;
				m_iPlayer2Selection = SelectRight(m_iPlayer2Selection);
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1)
			{
				playMenuEnter = true;
				m_bPlayer2Selected = true;
				PlayerManager::GetInstance().ePlayer2Element = SetPlayerElement(m_iPlayer2Selection);
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad2)
			{
				LevelLoader::LoadLevel(LEVELS::MENUSCENE);
			}
		}
		else if (Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad2)
		{
			m_bPlayer2Selected = false;
		}
	}
	else
	{
		GUI::GetInstance().HandleEvents();
	}

	if (playMenuMove)
	{
		playMenuMove = false;
		AudioManager::PlayAudioSource("MenuMove");
	}
	if (playMenuEnter)
	{
		playMenuEnter = false;
		AudioManager::PlayAudioSource("MenuEnter");
	}
}

void CharacterSelectScene::Update()
{
	GUI::GetInstance().Update();

	if (!m_bPlayer1Selected) 
	{
		ScaleImage("Player1");
		SetPlayerPosition("Player1", m_iPlayer1Selection);
	}

	if (!m_bPlayer2Selected) 
	{
		ScaleImage("Player2");
		SetPlayerPosition("Player2", m_iPlayer2Selection);
	}

	if (m_bPlayer1Selected && m_bPlayer2Selected)
	{
		ScaleSelectedButton("Start");
	}

}

void CharacterSelectScene::Draw()
{
	Statics::RenderWindow.draw(GUI::GetInstance());
}

void CharacterSelectScene::ScaleSelectedButton(std::string _button)
{
	Button* button = GUI::GetInstance().GetButton(_button);

	if (button)
	{
		float throb = 1 + sinf(ToRad((float)Statics::Time.getElapsedTime().asMilliseconds())) / 10;
		button->SetScale({ throb, throb });
	}
}

void CharacterSelectScene::ScaleImage(std::string _image)
{
	float throb = 1 + sinf(ToRad((float)Statics::Time.getElapsedTime().asMilliseconds())) / 20;
	throb /= 2.0f;
	(GUI::GetInstance().GetImage(_image)).setScale({ throb, throb });
}

int CharacterSelectScene::SelectLeft(int _player)
{
	int thisPlayer, otherPlayer;
	if (_player == m_iPlayer1Selection)
	{
		thisPlayer = m_iPlayer1Selection;
		otherPlayer = m_iPlayer2Selection;
	}
	else {
		thisPlayer = m_iPlayer2Selection;
		otherPlayer = m_iPlayer1Selection;
	}

	if (thisPlayer - 1 != 0)
	{
		if (thisPlayer - 1 != otherPlayer)
		{
			thisPlayer--;
		}
		else if (thisPlayer - 2 == 1) {
			thisPlayer = 1;
		}
	}
	return thisPlayer;
}

int CharacterSelectScene::SelectRight(int _player)
{
	int thisPlayer, otherPlayer;
	if (_player == m_iPlayer1Selection)
	{
		thisPlayer = m_iPlayer1Selection;
		otherPlayer = m_iPlayer2Selection;
	}
	else {
		thisPlayer = m_iPlayer2Selection;
		otherPlayer = m_iPlayer1Selection;
	}

	if (thisPlayer + 1 != 4)
	{
		if (thisPlayer + 1 != otherPlayer)
		{
			thisPlayer++;
		}
		else if (thisPlayer + 2 == 3)
		{
			thisPlayer = 3;
		}
	}
	return thisPlayer;
}

void CharacterSelectScene::SetPlayerPosition(std::string _player, int _playerPosition)
{
	switch (_playerPosition) {
	case 1:
	{
		(GUI::GetInstance().GetImage(_player)).setPosition(m_v2fPosition1);
		break;
	}
	case 2:
	{
		(GUI::GetInstance().GetImage(_player)).setPosition(m_v2fPosition2);
		break;
	}
	case 3:
	{
		(GUI::GetInstance().GetImage(_player)).setPosition(m_v2fPosition3);
		break;
	}
	}
}

ELEMENTTYPE CharacterSelectScene::SetPlayerElement(int _player)
{
	switch (_player)
	{
		case 1:
		{
			return ELEMENTTYPE::FIRE;
			break;
		}
		case 2:
		{
			return ELEMENTTYPE::EARTH;
			break;
		}
		case 3:
		{
			return ELEMENTTYPE::WATER;
			break;
		}
		default:
			break;
	}

	return ELEMENTTYPE::NONE;
}
