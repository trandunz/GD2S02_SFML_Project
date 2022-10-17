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

#define MAX_SCORES_DISPLAY 10
#define RECORD_FONTSIZE 36
//Value obtained through trial and error
//to get the correct change in position when moving
//the indicator
#define NEWRECORD_FONTWIDTH 26
#define INPUTMODE_POSITIONOFFSET 42
#define SEPERATOR ","

class Animator;

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
		std::string sName1{ "   " };
		std::string sName2{ "   " };
		std::string sScore{ '0' };
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
	/// Writes the current scores into the data file
	/// </summary>
	void RecordScores();
	/// <summary>
	/// Create the text objects that will help to display
	/// the list of high scores
	/// </summary>
	void CreateScoreDisplay();
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
	/// Meant to handle player inputs when attempting to create their initials
	/// for aa new high scores
	/// </summary>
	/// <param name="_inRank"></param>
	virtual void ParsePlayerCharacterInputs();
	/// <summary>
	/// Moves the entry (at the given rank) one rank down
	/// </summary>
	/// <param name="_inRankToMoveDown"></param>
	void MoveScoreDown(unsigned _inRankToMoveDown);
	/// <summary>
	/// Move other rank entries down by an offset, 
	/// and move the new entry down slightly and increase its size
	/// </summary>
	/// <param name="_inRank"></param>
	/// <param name="_inOffset"></param>
	void AdjustDisplayForInput(unsigned _inRank, int _inOffset);

	const std::string m_ksFileLocation = "Resources/Data/HighScores.csv";
	const std::string m_ksSelectorFileLocation_P1 = "CharacterSelector_P1.png";
	const std::string m_ksSelectorFileLocation_P2 = "CharacterSelector_P2.png";

	bool m_bReadOnly{ true };
	std::map<unsigned, HighScoreEntry> m_mapScoreList;

	unsigned m_uCharIndex_P1{0};
	unsigned m_uCharIndex_P2{0};
	unsigned m_uNewScoreRank = 0;

	Animator* m_pIndicator_P1 = nullptr;
	Animator* m_pIndicator_P2 = nullptr;

	bool m_bPlayer1_Finish{false};
	bool m_bPlayer2_Finish{false};

	char m_cNameInput_P1[3]{'A','A','A'};
	char m_cNameInput_P2[3]{'A','A','A'};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};