// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : GameScene.cpp 
// Description : GameScene Implementation File		
// Author : Inman, Will

#include "GameScene.h"
#include "PlayerManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "VFX.h"
#include "GUI.h"
#include "Math.h"
#include "TextureLoader.h"
#include "AudioManager.h"
#include "EndGameMenu.h"

GameScene::GameScene()
{
	PlayerManager::GetInstance().CreatePlayer(
		{ 
			//&TextureLoader::LoadTexture(Statics::sPlayer1Element),
			{200, 600},
			{32,32},
			{16},
			{300},
			3,
			3,
			true
			
		});

	PlayerManager::GetInstance().CreatePlayer(
		{
			//&TextureLoader::LoadTexture(Statics::sPlayer2Element),
			{Statics::RenderWindow.getSize().x - 200.0f, 600},
			{32,32},
			{16},
			{300},
			3,
			3,
			false
		});

	GUI::GetInstance().CreateText("Score",
		{
			{Statics::RenderWindow.getView().getCenter().x,20}, // Position
			"", // Text / string
			{255, 215, 0} // Colour (Gold)
		}
		);

	CreateScrollingBackground();

	// Music
	AudioManager::PlayMusic("Music_GamePlay.wav", true);

	// SFX
	AudioManager::CreateAudioSource("Primary", "primary.wav");
	AudioManager::CreateAudioSource("ShamanSpell", "shaman.wav");
	AudioManager::CreateAudioSource("Secondary", "secondary.wav");
	AudioManager::CreateAudioSource("Special", "special.wav");
	AudioManager::CreateAudioSource("Bow", "bow.wav");
	AudioManager::CreateAudioSource("PlayerDeath", "death.wav");
	AudioManager::CreateAudioSource("EnemyDeath", "kill.wav");
	AudioManager::CreateAudioSource("PickupHeart", "pickup_heart.wav");
	AudioManager::CreateAudioSource("PickupMana", "pickup_mana.wav");
	AudioManager::CreateAudioSource("Hit", "hit.wav");
	AudioManager::CreateAudioSource("Warrior", "warrior.wav");
	AudioManager::CreateAudioSource("CantCast", "cant_cast.wav");

}

GameScene::~GameScene()
{
	if (m_PauseMenu)
	{
		delete m_PauseMenu;
		m_PauseMenu = nullptr;
	}
	if (m_EndGameMenu)
	{
		delete m_EndGameMenu;
		m_EndGameMenu = nullptr;
	}

	ObjectManager::GetInstance().CleanupEverything();
	ProjectileManager::GetInstance().CleanupProjectiles();
	PlayerManager::GetInstance().CleanupPlayers();
	EnemyManager::GetInstance().CleanupEnemies();
	GUI::GetInstance().CleanupElements();
	VFX::GetInstance().CleanupElements();
}

void GameScene::HandleEvents()
{
	PlayerManager::GetInstance().HandleEvents();
	GUI::GetInstance().HandleEvents();

	if (Statics::EventHandle.type == sf::Event::KeyPressed)
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Escape)
		{
			if (m_bGameOver == false)
			{
				if (m_PauseMenu)
				{
					m_PauseMenu->bDestroy = true;
				}
				else
				{
					m_PauseMenu = new PauseMenu();
				}
			}
		}
	}
}

void GameScene::Update()
{
	ProjectileManager::GetInstance().Update();
	EnemyManager::GetInstance().Update();
	ObjectManager::GetInstance().Update();
	PlayerManager::GetInstance().Update();
	GUI::GetInstance().Update();
	VFX::GetInstance().Update();
	if (m_PauseMenu)
		m_PauseMenu->Update();

	ScrollBackground();
	//GUI::GetInstance().SetText("Score", "Score: " + FloatToString(m_fDistanceTravelled, 0)); // Changing to on killing enemy
	GUI::GetInstance().SetText("Score", "Score: " + FloatToString(Statics::fGameScore, 0));

	ProjectileManager::GetInstance().CleanupDestroyed();
	ObjectManager::GetInstance().CleanupDestroyed();
	EnemyManager::GetInstance().CleanupDestroyed();
	PlayerManager::GetInstance().CleanupDestroyed();
	CleanupPauseMenuIfDestroyed();

	if (PlayerManager::GetInstance().GetPlayers().size() <= 0
		&& m_bGameOver == false)
	{
		m_bGameOver = true;
		m_EndGameMenu = new EndGameMenu;
	}

	m_fElaspedTime += Statics::fDeltaTime;
}

void GameScene::Draw()
{
	for (auto& background : m_vecBackgrounds)
		Statics::RenderWindow.draw(background);

	Statics::RenderWindow.draw(ObjectManager::GetInstance());
	Statics::RenderWindow.draw(EnemyManager::GetInstance());
	Statics::RenderWindow.draw(ProjectileManager::GetInstance());
	Statics::RenderWindow.draw(PlayerManager::GetInstance());
	Statics::RenderWindow.draw(VFX::GetInstance());
	Statics::RenderWindow.draw(GUI::GetInstance());
}

void GameScene::CreateScrollingBackground()
{
	m_vecBackgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("Terrain/map.png")));
	m_vecBackgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("Terrain/map.png")));
	for (auto& background : m_vecBackgrounds)
	{
		SetOriginCenter(background); 
	}
	m_vecBackgrounds[0].setPosition(400, 0);
	m_vecBackgrounds[1].setPosition(400, 9600);
}

void GameScene::ScrollBackground()
{
	m_fDistanceTravelled += Statics::fBackgroundScrollSpeed * Statics::fDeltaTime;
	for (auto& background : m_vecBackgrounds)
	{
		background.move({ 0,Statics::fBackgroundScrollSpeed * Statics::fDeltaTime });
		if (background.getPosition().y - Statics::RenderWindow.getView().getCenter().y
			>= background.getGlobalBounds().height)
		{
			background.move({ 0, -2 * background.getGlobalBounds().height + 1 });
		}
	}
}

void GameScene::CleanupPauseMenuIfDestroyed()
{
	if (m_PauseMenu)
	{
		if (m_PauseMenu->bDestroy)
		{
			delete m_PauseMenu;
			m_PauseMenu = nullptr;
		}
	}
}
