// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : LevelLoader.cpp 
// Description : LevelLoader Implementation File		
// Author : Inman, Will

#include "LevelLoader.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "CharacterSelectScene.h"

Level* LevelLoader::CurrentLevel = nullptr;
LEVELS LevelLoader::LevelToLoad = LEVELS::UNASSIGNED;

void LevelLoader::HandleEvents()
{
	if (CurrentLevel != nullptr)
	{
		CurrentLevel->HandleEvents();
	}
}

void LevelLoader::Update()
{
	if (CurrentLevel != nullptr)
	{
		CurrentLevel->Update();
	}
}

void LevelLoader::Draw()
{
	if (CurrentLevel != nullptr)
	{
		CurrentLevel->Draw();
	}
}

void LevelLoader::SwitchToLoadedLevel()
{
	if (LevelToLoad != LEVELS::UNASSIGNED)
	{
		CleanupLevel();
		switch (LevelToLoad)
		{
		case LEVELS::MENUSCENE:
		{
			CurrentLevel = new MenuScene();
			break;
		}
		case LEVELS::CHARACTERSELECTSCENE:
		{
			CurrentLevel = new CharacterSelectScene();
			break;
		}
		case LEVELS::GAMESCENE:
		{
			CurrentLevel = new GameScene();
			break;
		}
		default:
			break;
		}

		LevelToLoad = LEVELS::UNASSIGNED;
	}
}

void LevelLoader::LoadLevel(LEVELS _newLevel)
{
	LevelToLoad = _newLevel;
}

void LevelLoader::CleanupLevel()
{
	if (CurrentLevel != nullptr)
	{
		delete CurrentLevel;
		CurrentLevel = nullptr;
	}
}
