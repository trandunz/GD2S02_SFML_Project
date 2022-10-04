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
			ScreenCentre, // Position
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
		muteEffectsTexture = &TextureLoader::LoadTexture("GUI/VolumeButton_Muted.png");
	else
		muteEffectsTexture = &TextureLoader::LoadTexture("GUI/VolumeButton.png");
	GUI::GetInstance().CreateButton("MuteEffects", // Key
		{
			"", // Label / String
			{ ScreenCentre.x - 21 ,ScreenCentre.y + 10}, // Position
			[this]()
			{
				AudioManager::ToggleMuteEffects();
				if (AudioManager::IsEffectsMuted())
					GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/VolumeButton_Muted.png");
				else
					GUI::GetInstance().GetButton("MuteEffects")->SetTexture("GUI/VolumeButton.png");
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
}

void SettingsMenu::CleanupElements()
{
	GUI::GetInstance().CleanupImageElement("SettingsMenuBackground");
	GUI::GetInstance().CleanupImageElement("SettingsMenuDullBackground");
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
}
