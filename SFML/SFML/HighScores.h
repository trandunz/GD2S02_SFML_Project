// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : HighScores.h 
// 
// Description :
//		
// Author : Chuang, Kee

#pragma once
#include "Level.h"
#include "Statics.h"


#define MAX_SCORES_DISPLAY 15
#define SEPERATOR ","

struct HighScoreEntry
{
	std::string sName1{};
	std::string sName2{};
	std::string sScore{};};


class HighScores : public Level
{
public:
	HighScores(bool _readOnly = true);
	virtual ~HighScores();

	/// <summary>
	/// Mainly handles input events
	/// </summary>
	virtual void HandleEvents() override;
	/// <summary>
	/// Handles any necessary update calls, which would likely be any animations
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// Handles drawing aany visual elements
	/// </summary>
	virtual void Draw() override;

private:
	/// <summary>
	/// Sets up the intial list of high scores
	/// </summary>
	void InitializeHighScores();
	/// <summary>
	/// Reads the scores from the data file and stores them
	/// </summary>
	void ReadScores();
	/// <summary>
	/// Create the text objects that will help to display
	/// the list of high scores
	/// </summary>
	void DisplayScores();

	bool m_bReadOnly = true;
	std::map<unsigned, HighScoreEntry> m_ScoreList;

	const std::string m_ksFileLocation = "Resources/Data/HighScores.csv";

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};