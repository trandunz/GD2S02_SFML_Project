// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : LevelLoader.h 
// Description : LevelLoader Header File
// Author : Inman, Will

#pragma once
#include "Level.h"

enum class LEVELS
{
	UNASSIGNED,

	MENUSCENE,
	GAMESCENE
};

class LevelLoader
{
public:
	static void HandleEvents();
	static void Update();
	static void Draw();
	
	static void SwitchToLoadedLevel();
	static void LoadLevel(LEVELS _newLevel);
	static void CleanupLevel();
private:
	static Level* CurrentLevel;
	static LEVELS LevelToLoad;
};

