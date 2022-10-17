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
	UNASSIGNED = 0,

	MENUSCENE,
	CHARACTERSELECTSCENE,
	GAMESCENE,
	HIGHSCORESCENE
};

class LevelLoader
{
public:
	/// <summary>
	/// Calls handle events on active seen if available
	/// </summary>
	static void HandleEvents();
	/// <summary>
	/// Calls Update on active seen if available
	/// </summary>
	static void Update();
	/// <summary>
	/// Calls Draw on active seen if available
	/// </summary>
	static void Draw();
	
	/// <summary>
	/// Switches to the currently loaded level if one is available
	/// </summary>
	static void SwitchToLoadedLevel();

	/// <summary>
	/// Proposes a level to be loaded at end of frame
	/// </summary>
	static void LoadLevel(LEVELS _newLevel);

	/// <summary>
	/// Cleans up the current level if available
	/// </summary>
	static void CleanupLevel();

	/// <summary>
	/// Returns the elapsed time of the current level
	/// </summary>
	static float GetElaspedTime();
private:
	static Level* CurrentLevel;
	static LEVELS LevelToLoad;

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

