// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : SettingsMenu.cpp 
// Description : SettingsMenu Implementation File		
// Author : 

#include "SettingsMenu.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "LevelLoader.h"
#include "AudioManager.h"
#include "Helper.h"

SettingsMenu::SettingsMenu()
{
	CreateMenuBackground();
	CreateMenuText();
	CreateMenuButtons();
	m_sAudioType = "MusicVolume";
}

SettingsMenu::~SettingsMenu()
{
	CleanupElements();
}

void SettingsMenu::HandleEvents()
{
	bool playMenuMove = false;
	bool playMenuSelect = false;

	if (Statics::EventHandle.type == sf::Event::KeyPressed && m_bButtonReleased)
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::W ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Up)
		{
			m_sAudioType = "MusicVolume";
			playMenuMove = true;
			m_bButtonReleased = false;
		}
		if(Statics::EventHandle.key.code == sf::Keyboard::Key::S ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Down)
		{
			m_sAudioType = "EffectsVolume";
			playMenuMove = true;
			m_bButtonReleased = false;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::A ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Left)
		{
			m_sAdjustAudio = "Decrease";
			playMenuSelect = true;
			m_bButtonReleased = false;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::D ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Right)
		{
			m_sAdjustAudio = "Increase";
			playMenuSelect = true;
			m_bButtonReleased = false;
		}
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Num1)
		{
			if (m_sAudioType == "EffectsVolume")
			{
				AudioManager::ToggleMuteEffects();
			}
			else {
			AudioManager::ToggleMuteMusic();
			}
			UnMuteIconChange(m_sAudioType);
			playMenuMove = true;
			m_bButtonReleased = false;
		}
	}
	// Allow audio to play once
	if (playMenuMove)
	{
		playMenuMove = false;
		AudioManager::PlayAudioSource("MenuMove");
	}
	else if (playMenuSelect)
	{
		playMenuSelect = false;
		AdjustVolume(m_sAdjustAudio, m_sAudioType);
	}

	if (Statics::EventHandle.type == sf::Event::KeyReleased)
	{
		m_bButtonReleased = true;
	}
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
			ScreenCentre, // Position
			{0.3f, 0.3f}
		});

	GUI::GetInstance().CreateImage("PlayerOneControlsBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			{ScreenCentre.x - 225.0f, ScreenCentre.y }, // Position
			{0.3f, 0.3f}
		});
	GUI::GetInstance().CreateImage("PlayerTwoControlsBackground", // Key
		{
			&TextureLoader::LoadTexture("GUI/PauseMenuBackground.png"), // Texture
			{ScreenCentre.x + 225.0f, ScreenCentre.y}, // Position
			{0.3f, 0.3f}
		});
}

void SettingsMenu::CreateMenuButtons()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();
	GUI::GetInstance().CreateButton("Back", // Key
		{
			"", // Label / String
			{ ScreenCentre.x,ScreenCentre.y + 80}, // Position
			[this]()
			{
				bDestroy = true; // On Press Lambda
			},
			& TextureLoader::LoadTexture("GUI/Back.png"),
			{0.9f,0.9f}, // Scale
		});
	GUI::GetInstance().CreateButton("IncreaseMusicVolume", // Key
		{
			"+", // Label / String
			{ ScreenCentre.x + 60,ScreenCentre.y - 40}, // Position
			[this]()
			{
				AudioManager::IncrementMusicVolume(10.0f);
				GUI::GetInstance().GetButton("MusicVolume")->SetLabel(FloatToString(AudioManager::GetMusicVolume() / 10, 0));
			},
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1,1}, // Scale
		});
	GUI::GetInstance().CreateButton("DecreaseMusicVolume", // Key
		{
			"-", // Label / String
			{ ScreenCentre.x - 60,ScreenCentre.y - 40}, // Position
			[this]()
			{
				AudioManager::DecrementMusicVolume(10.0f);
				GUI::GetInstance().GetButton("MusicVolume")->SetLabel(FloatToString(AudioManager::GetMusicVolume() / 10, 0));
			},
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1,1}, // Scale
		});

	GUI::GetInstance().CreateButton("IncreaseEffectsVolume", // Key
		{
			"+", // Label / String
			{ ScreenCentre.x + 60,ScreenCentre.y + 10}, // Position
			[this]()
			{
				AudioManager::IncrementEffectsVolume(10.0f);
				GUI::GetInstance().GetButton("EffectsVolume")->SetLabel(FloatToString(AudioManager::GetEffectsVolume() / 10, 0));
			},
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1,1}, // Scale
		});
	GUI::GetInstance().CreateButton("DecreaseEffectsVolume", // Key
		{
			"-", // Label / String
			{ ScreenCentre.x - 60,ScreenCentre.y + 10}, // Position
			[this]()
			{
				AudioManager::DecrementEffectsVolume(10.0f);
				GUI::GetInstance().GetButton("EffectsVolume")->SetLabel(FloatToString(AudioManager::GetEffectsVolume() / 10,0));
			},
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1,1}, // Scale
		});

	sf::Texture* muteEffectsTexture = nullptr;
	if (AudioManager::IsEffectsMuted())
		muteEffectsTexture = &TextureLoader::LoadTexture("GUI/EffectsButton_Muted.png");
	else
		muteEffectsTexture = &TextureLoader::LoadTexture("GUI/EffectsButton.png");
	GUI::GetInstance().CreateButton("MuteEffects", // Key
		{
			"", // Label / String
			{ ScreenCentre.x - 21 ,ScreenCentre.y + 10}, // Position
			[this]()
			{
				AudioManager::ToggleMuteEffects();
				if (AudioManager::IsEffectsMuted())
					GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/EffectsButton_Muted.png");
				else
					GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/EffectsButton.png");
			},
			muteEffectsTexture,
			{1.25f,1.25f}, // Scale
		});
	muteEffectsTexture = nullptr;

	GUI::GetInstance().CreateButton("EffectsVolume", // Key
		{
			FloatToString(AudioManager::GetEffectsVolume() / 10, 0), // Label / String
			{ ScreenCentre.x + 21 ,ScreenCentre.y + 10}, // Position
			nullptr,
			& TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.25f,1.25f}, // Scale
		});

	sf::Texture* muteMusicTexture = nullptr;
	if (AudioManager::IsMusicMuted())
		muteMusicTexture = &TextureLoader::LoadTexture("GUI/MusicButton_Muted.png");
	else
		muteMusicTexture = &TextureLoader::LoadTexture("GUI/MusicButton.png");
	GUI::GetInstance().CreateButton("MuteMusic", // Key
		{
			"", // Label / String
			{ ScreenCentre.x - 21 ,ScreenCentre.y - 40}, // Position
			[this]()
			{
				AudioManager::ToggleMuteMusic();
				if (AudioManager::IsMusicMuted())
					GUI::GetInstance().GetButton("MuteMusic")->SetTexture("GUI/MusicButton_Muted.png");
				else
					GUI::GetInstance().GetButton("MuteMusic")->SetTexture("GUI/MusicButton.png");
			},
			muteMusicTexture,
			{1.25f,1.25f}, // Scale
		});
	muteMusicTexture = nullptr;

	GUI::GetInstance().CreateButton("MusicVolume", // Key
		{
			FloatToString(AudioManager::GetMusicVolume() / 10, 0), // Label / String
			{ ScreenCentre.x + 21 ,ScreenCentre.y - 40}, // Position
			nullptr,
			& TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.25f,1.25f}, // Scale
		});
}

void SettingsMenu::CreateMenuText()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("SettingsMenuTitle", // Key
		{
			{ScreenCentre.x, ScreenCentre.y - 100}, // Position
			"Settings" // Label / String
		});

	CreatePlayerOneKeybinds();
	CreatePlayerTwoKeybinds();
}

void SettingsMenu::CleanupElements()
{
	GUI::GetInstance().CleanupImageElement("SettingsMenuBackground");
	GUI::GetInstance().CleanupImageElement("SettingsMenuDullBackground");
	GUI::GetInstance().CleanupImageElement("PlayerOneControlsBackground");
	GUI::GetInstance().CleanupImageElement("PlayerTwoControlsBackground");
	GUI::GetInstance().CleanupTextElement("SettingsMenuTitle");
	GUI::GetInstance().CleanupButtonElement("Back");
	GUI::GetInstance().CleanupButtonElement("DecreaseMusicVolume");
	GUI::GetInstance().CleanupButtonElement("IncreaseMusicVolume");
	GUI::GetInstance().CleanupButtonElement("MuteMusic");
	GUI::GetInstance().CleanupButtonElement("DecreaseEffectsVolume");
	GUI::GetInstance().CleanupButtonElement("IncreaseEffectsVolume");
	GUI::GetInstance().CleanupButtonElement("MuteEffects");
	GUI::GetInstance().CleanupButtonElement("MusicVolume");
	GUI::GetInstance().CleanupButtonElement("EffectsVolume");

	GUI::GetInstance().CleanupTextElement("PlayerOneControls");
	GUI::GetInstance().CleanupTextElement("P1MoveUp");
	GUI::GetInstance().CleanupTextElement("P1MoveDown");
	GUI::GetInstance().CleanupTextElement("P1MoveLeft");
	GUI::GetInstance().CleanupTextElement("P1MoveRight");
	GUI::GetInstance().CleanupTextElement("P1BasicAttack");
	GUI::GetInstance().CleanupTextElement("P1SecondaryAttack");
	GUI::GetInstance().CleanupTextElement("P1SpecialAttack");
	GUI::GetInstance().CleanupTextElement("PlayerTwoControls");
	GUI::GetInstance().CleanupTextElement("P2MoveUp");
	GUI::GetInstance().CleanupTextElement("P2MoveDown");
	GUI::GetInstance().CleanupTextElement("P2MoveLeft");
	GUI::GetInstance().CleanupTextElement("P2MoveRight");
	GUI::GetInstance().CleanupTextElement("P2BasicAttack");
	GUI::GetInstance().CleanupTextElement("P2SecondaryAttack");
	GUI::GetInstance().CleanupTextElement("P2SpecialAttack");

	GUI::GetInstance().CleanupButtonElement("P1MoveUp");
	GUI::GetInstance().CleanupButtonElement("P1MoveDown");
	GUI::GetInstance().CleanupButtonElement("P1MoveLeft");
	GUI::GetInstance().CleanupButtonElement("P1MoveRight");
	GUI::GetInstance().CleanupButtonElement("P1BasicAttack");
	GUI::GetInstance().CleanupButtonElement("P1SecondaryAttack");
	GUI::GetInstance().CleanupButtonElement("P1SpecialAttack");
	GUI::GetInstance().CleanupButtonElement("P2MoveUp");
	GUI::GetInstance().CleanupButtonElement("P2MoveDown");
	GUI::GetInstance().CleanupButtonElement("P2MoveLeft");
	GUI::GetInstance().CleanupButtonElement("P2MoveRight");
	GUI::GetInstance().CleanupButtonElement("P2BasicAttack");
	GUI::GetInstance().CleanupButtonElement("P2SecondaryAttack");
	GUI::GetInstance().CleanupButtonElement("P2SpecialAttack");
}

void SettingsMenu::CreatePlayerOneKeybinds()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("PlayerOneControls", // Key
		{
			{ScreenCentre.x - 225.0f, ScreenCentre.y - 120.0f}, // Position
			"Player One", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateText("P1MoveUp", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y - 80.0f}, // Position
			"Up", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1MoveUp", // Key
		{
			"W", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y - 80.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1MoveDown", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y - 50.0f}, // Position
			"Down", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1MoveDown", // Key
		{
			"S", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y - 50.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1MoveLeft", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y - 20.0f}, // Position
			"Left", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1MoveLeft", // Key
		{
			"A", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y - 20.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1MoveRight", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y + 10}, // Position
			"Right", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1MoveRight", // Key
		{
			"D", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y + 10}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1BasicAttack", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y + 40.0f}, // Position
			"Attack", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1BasicAttack", // Key
		{
			"V", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y + 40}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1SecondaryAttack", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y + 70.0f}, // Position
			"Secondary", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1SecondaryAttack", // Key
		{
			"B", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y + 70}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P1SpecialAttack", // Key
		{
			{ScreenCentre.x - 250.0f, ScreenCentre.y + 100.0f}, // Position
			"Special", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P1SpecialAttack", // Key
		{
			"N", // Label / String
			{ScreenCentre.x - 180.0f, ScreenCentre.y + 100.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/CircleButton.png"),
			{1.0f,1.0f}, // Scale
		});
}

void SettingsMenu::CreatePlayerTwoKeybinds()
{
	sf::Vector2f ScreenCentre = Statics::RenderWindow.getView().getCenter();

	GUI::GetInstance().CreateText("PlayerTwoControls", // Key
		{
			{ScreenCentre.x + 225.0f, ScreenCentre.y - 120.0f}, // Position
			"Player Two", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateText("P2MoveUp", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y - 80.0f}, // Position
			"Up", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2MoveUp", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y - 80.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/UpButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2MoveDown", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y - 50.0f}, // Position
			"Down", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2MoveDown", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y - 50.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/DownButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2MoveLeft", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y - 20.0f}, // Position
			"Left", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2MoveLeft", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y - 20.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/LeftButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2MoveRight", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y + 10}, // Position
			"Right", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2MoveRight", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y + 10}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/RightButton.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2BasicAttack", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y + 40.0f}, // Position
			"Attack", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2BasicAttack", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y + 40}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/num1.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2SecondaryAttack", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y + 70.0f}, // Position
			"Secondary", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2SecondaryAttack", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y + 70}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/num2.png"),
			{1.0f,1.0f}, // Scale
		});
	GUI::GetInstance().CreateText("P2SpecialAttack", // Key
		{
			{ScreenCentre.x + 200.0f, ScreenCentre.y + 100.0f}, // Position
			"Special", // Label / String,
			{99, 99, 99},
			22,
			{255, 255, 255}
		});
	GUI::GetInstance().CreateButton("P2SpecialAttack", // Key
		{
			"", // Label / String
			{ScreenCentre.x + 270.0f, ScreenCentre.y + 100.0f}, // Position
			nullptr,
			&TextureLoader::LoadTexture("GUI/num3.png"),
			{1.0f,1.0f}, // Scale
		});
}

void SettingsMenu::AdjustVolume(std::string _increaseOrDecrease, std::string _volumeToAdjust)
{

	AudioManager::PlayAudioSource("MenuMove");
	Button* button = nullptr;

	button = GUI::GetInstance().GetButton(_increaseOrDecrease + _volumeToAdjust);
	if (button)
		button->CallOnPress();

	button = nullptr;

	UnMuteIconChange(_volumeToAdjust);
}

void SettingsMenu::UnMuteIconChange(std::string _audioType)
{

	if (_audioType == "EffectsVolume")
	{
		if (AudioManager::IsEffectsMuted())
			GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/EffectsButton_Muted.png");
		else
			GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/EffectsButton.png");
	}
	else {
		if (AudioManager::IsMusicMuted())
			GUI::GetInstance().GetButton("MuteMusic")->SetTexture("GUI/MusicButton_Muted.png");
		else
			GUI::GetInstance().GetButton("MuteMusic")->SetTexture("GUI/MusicButton.png");
	}
}
