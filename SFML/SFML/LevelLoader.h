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

