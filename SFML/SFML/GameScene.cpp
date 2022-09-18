#include "GameScene.h"
#include "PlayerManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "VFX.h"
#include "GUI.h"
#include "Math.h"
#include "TextureLoader.h"

GameScene::GameScene()
{
	PlayerManager::GetInstance().CreatePlayer(
		{ 
			&TextureLoader::LoadTexture("Unit/Player/Earth_Mage.png"),
			{200, 600},
			{32,32},
			{16},
			{300}
			
		});

	PlayerManager::GetInstance().CreatePlayer(
		{
			&TextureLoader::LoadTexture("Unit/Player/Fire_Mage.png"),
			{600, 600},
			{32,32},
			{16},
			{300},
			3,
			3,
			false
		});

	GUI::GetInstance().CreateText("Score",
		{
			{400,20}
		}
		);

	CreateScrollingBackground();
}

GameScene::~GameScene()
{
	ObjectManager::GetInstance().CleanupObstacles();
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
}

void GameScene::Update()
{
	ProjectileManager::GetInstance().Update();
	EnemyManager::GetInstance().Update();
	ObjectManager::GetInstance().Update();
	PlayerManager::GetInstance().Update();
	GUI::GetInstance().Update();
	VFX::GetInstance().Update();

	ScrollBackground();
	//GUI::GetInstance().SetText("Score", "Score: " + FloatToString(m_fDistanceTravelled, 0)); // Changing to on killing enemy
	GUI::GetInstance().SetText("Score", "Score: " + FloatToString(Statics::fGameScore, 0));

	ProjectileManager::GetInstance().CleanupDestroyed();
	EnemyManager::GetInstance().CleanupDestroyed();
	PlayerManager::GetInstance().CleanupDestroyed();
}

void GameScene::Draw()
{
	for (auto& background : m_Backgrounds)
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
	m_Backgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("Terrain/map.png")));
	m_Backgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("Terrain/map.png")));
	for (auto& background : m_Backgrounds)
	{
		SetOriginCenter(background);
		//background.setScale({ 2.66666666f,2.666666666f }); 
	}
	m_Backgrounds[0].setPosition(400, 0);
	m_Backgrounds[1].setPosition(400, 9600);
}

void GameScene::ScrollBackground()
{
	m_fDistanceTravelled += Statics::fBackgroundScrollSpeed * Statics::fDeltaTime;
	for (auto& background : m_Backgrounds)
	{
		background.move({ 0,Statics::fBackgroundScrollSpeed * Statics::fDeltaTime });
		if (background.getPosition().y - Statics::RenderWindow.getView().getCenter().y
			>= background.getGlobalBounds().height)
		{
			background.move({ 0,- 2 *background.getGlobalBounds().height });
		}
	}
}
