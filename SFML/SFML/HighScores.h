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

class HighScores : public Level
{
public:
	HighScores();
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

	struct HighScoreEntry
	{
		std::string sName1{};
		std::string sName2{};
		std::string sScore{};
	};

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
	/// <summary>
	/// Update the text objects to reflect the new scores
	/// </summary>
	void UpdateScores();
	/// <summary>
	/// Checks if the provided score is a new high score.
	/// returns the its rank if it is. Otherwiser returns -1
	/// </summary>
	/// <param name="_inScore"></param>
	/// <returns></returns>
	virtual int CheckIfNewHighScore();
	/// <summary>
	/// Setup recognizing input for adding new entry to high score.
	/// Takes in the rank of the new entry
	/// </summary>
	/// <param name="_inRank"></param>
	virtual void StartInputModeOnRankEntry(unsigned _inRank);
	/// <summary>
	/// Moves the entry (at the given rank) one rank down
	/// </summary>
	/// <param name="_inRankToMoveDown"></param>
	void MoveScoreDown(unsigned _inRankToMoveDown);

	bool m_bReadOnly{ true };
	std::map<unsigned, HighScoreEntry> m_mapScoreList;

	unsigned m_uCharIndex_P1{0};
	unsigned m_uCharIndex_P2{0};

	char m_cNameInput_P1[3]{' '};
	char m_cNameInput_P2[3]{' '};

	const std::string m_ksFileLocation = "Resources/Data/HighScores.csv";

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};