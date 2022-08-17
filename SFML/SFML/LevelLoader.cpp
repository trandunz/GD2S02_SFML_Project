#include "LevelLoader.h"

Level* LevelLoader::CurrentLevel = nullptr;

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

void LevelLoader::LoadLevel(Level* _level)
{
	CleanupLevel();
	if (CurrentLevel == nullptr)
	{
		CurrentLevel = _level;
	}
}

void LevelLoader::CleanupLevel()
{
	if (CurrentLevel != nullptr)
	{
		delete CurrentLevel;
		CurrentLevel = nullptr;
	}
}
