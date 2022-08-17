#include "GameScene.h"
#include "PlayerManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "GUI.h"
#include "Math.h"

GameScene::GameScene()
{
	PlayerManager::GetInstance().CreatePlayer(
		{ 
			&TextureLoader::LoadTexture("Earth_Mage.png"),
			{200, 600},
			{300}
		});

	PlayerManager::GetInstance().CreatePlayer(
		{
			&TextureLoader::LoadTexture("Earth_Mage.png"),
			{600, 600},
			{300},
			3,
			false
		});

	//ObjectManager::GetInstance().CreateObstacle(
	//	{ 
	//		&TextureLoader::LoadTexture("Rock_temp.png"),
	//		{400, 200},
	//		{0.05f, 0.05f}
	//	});

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

	ScrollBackground(200.0f);
	GUI::GetInstance().SetText("Score", "Score: " + FloatToString(m_fDistanceTravelled, 0));

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
	Statics::RenderWindow.draw(GUI::GetInstance());
}

void GameScene::CreateScrollingBackground()
{
	m_Backgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("map.png")));
	m_Backgrounds.emplace_back(sf::Sprite(TextureLoader::LoadTexture("map.png")));
	for (auto& background : m_Backgrounds)
	{
		SetOriginCenter(background);
		//background.setScale({ 2.66666666f,2.666666666f }); 
	}
	m_Backgrounds[0].setPosition(400, 0);
	m_Backgrounds[1].setPosition(400, 9600);
}

void GameScene::ScrollBackground(float _speed)
{
	m_fDistanceTravelled += _speed * Statics::DeltaTime;
	for (auto& background : m_Backgrounds)
	{
		background.move({ 0,_speed * Statics::DeltaTime });
		if (background.getPosition().y - Statics::RenderWindow.getView().getCenter().y
			>= background.getGlobalBounds().height)
		{
			background.move({ 0,- 2 *background.getGlobalBounds().height });
		}
	}
}
