#pragma once
#include "MenuScene.h"

class LevelLoader
{
public:
	static void HandleEvents();
	static void Update();
	static void Draw();
	
	static void LoadLevel(Level* _level);
	static void CleanupLevel();
private:
	static Level* CurrentLevel;
};

