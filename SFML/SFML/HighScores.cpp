#include <fstream>
#include "HighScores.h"
#include "LevelLoader.h"
#include "TextureLoader.h"
#include "Helper.h"
#include "GUI.h"

HighScores::HighScores()
{
	InitializeHighScores();
	ReadScores();
	DisplayScores();

	if (Statics::fGameScore > 0.0f)
	{
		//m_bReadOnly = true;
		unsigned currentScoreRank = CheckIfNewHighScore();
		if ( currentScoreRank > 0)
		{
			StartInputModeOnRankEntry(currentScoreRank);
			UpdateScores();
			m_bReadOnly = true;
		}
	}
}

HighScores::~HighScores()
{
	if (!m_bReadOnly)
	{

	}

	GUI::GetInstance().CleanupElements();
}

void HighScores::HandleEvents()
{
	if (m_bReadOnly)
	{
		if (Statics::EventHandle.type == sf::Event::KeyPressed)
		{
			//Load main menu
			LevelLoader::LoadLevel(LEVELS::MENUSCENE);
		}
	}
	else
	{

	}
}

void HighScores::Update()
{
	GUI::GetInstance().Update();
}

void HighScores::Draw()
{
	Statics::RenderWindow.draw(GUI::GetInstance());
}

int HighScores::CheckIfNewHighScore()
{
	for (unsigned rank = 1; rank <= MAX_SCORES_DISPLAY; rank++)
	{
		if (Statics::fGameScore > std::stoi(m_mapScoreList.find(rank)->second.sScore) )
		{
			return rank;
		}
	}
	return -1;
}

void HighScores::InitializeHighScores()
{
	for (unsigned i = 1; i <= MAX_SCORES_DISPLAY; i++)
	{
		HighScoreEntry newEntry;
		m_mapScoreList.emplace(i, newEntry);
	}
}

void HighScores::ReadScores()
{
	std::ifstream dataFile;

	auto GetDataString = [](std::string& _line, std::size_t _point1, std::size_t _point2)
	{
		if (_point1 != std::string::npos)
		{
			return _line.substr(_point1, _point2);
		}
		else
		{
			return std::string();
		}
	};

	dataFile.open(m_ksFileLocation);
	if (dataFile.is_open())
	{
		std::string currentLine;
		unsigned currentIndex = 1;
		while (std::getline(dataFile, currentLine) && currentIndex<= MAX_SCORES_DISPLAY)
		{
			std::string name1{};
			std::string name2{};
			std::string score{};

			//Get the position of delimiters
			std::size_t delimiter_First = currentLine.find(SEPERATOR);
			std::size_t delimiter_Second = currentLine.find(SEPERATOR, delimiter_First+1);
			//Get the values
			name1 = GetDataString(currentLine, 0, delimiter_First);
			name2 = GetDataString(currentLine, delimiter_First+1, delimiter_Second - delimiter_First - 1);
			score = GetDataString(currentLine, delimiter_Second+1, std::string::npos);
			//Store the values in the map
			HighScoreEntry* currentEntry = &(m_mapScoreList.find(currentIndex)->second);
			currentEntry->sName1 = name1;
			currentEntry->sName2 = name2;
			currentEntry->sScore = score;

			currentIndex++;
		}
	}
	else
	{
		Print("ERR [HighScores]: Failed to open data file");		
	}

}

void HighScores::DisplayScores()
{
	//Each displayed score can be divided into 3 columns: rank, name and score
	//Here, the x coordinate for each coordinate is precalculated
	float firstColumnCoordinate = (Statics::RenderWindow.getView().getCenter().x) /3;
	float middleColumnCoordinate = (Statics::RenderWindow.getView().getCenter().x);
	float lastColumnCoordinate = (Statics::RenderWindow.getView().getCenter().x) * 5/ 3;

	TextProperties newTextProperties;
	newTextProperties.v2fStartPos = sf::Vector2f(middleColumnCoordinate, 40);
	newTextProperties.String = "HIGHSCORE";
	newTextProperties.OutlineColor = sf::Color::White;
	newTextProperties.iCharacterSize = 52;
	GUI::GetInstance().CreateText("SceneTitle", newTextProperties);

	newTextProperties.v2fStartPos = sf::Vector2f(firstColumnCoordinate, 85);
	newTextProperties.iCharacterSize = 42;
	newTextProperties.String = "Rank";
	GUI::GetInstance().CreateText("Rank_Label", newTextProperties);

	newTextProperties.v2fStartPos = sf::Vector2f(middleColumnCoordinate, 85);
	newTextProperties.String = "Name";
	GUI::GetInstance().CreateText("Name_Label", newTextProperties);

	newTextProperties.v2fStartPos = sf::Vector2f(lastColumnCoordinate, 85);
	newTextProperties.String = "Score";
	GUI::GetInstance().CreateText("Score_Label", newTextProperties);
	
	//Set the text size to be 36 henceforth
	newTextProperties.iCharacterSize = 36;
	//Set up text for each rank to be displayed
	for (unsigned rank = 1; rank <= MAX_SCORES_DISPLAY; rank++)
	{
		//Load the score and name at current rank
		HighScoreEntry currentRank = m_mapScoreList.find(rank)->second;

		//Set up a unique name for each text object that makes up each that
		//is to be displayed
		std::string textKey = "Rank" + std::to_string(rank);
		std::string nameKey = "Name" + std::to_string(rank);
		std::string scoreKey = "Score" + std::to_string(rank);

		//Finally, set up the 3 text objects for the current rank
		newTextProperties.v2fStartPos = sf::Vector2f(firstColumnCoordinate, 85 + (rank * 40));
		newTextProperties.String = std::to_string(rank);
		GUI::GetInstance().CreateText(textKey, newTextProperties);

		newTextProperties.v2fStartPos = sf::Vector2f(middleColumnCoordinate, 85 + (rank * 40));
		newTextProperties.String = currentRank.sName1 + "  &  " + currentRank.sName2;
		GUI::GetInstance().CreateText(nameKey, newTextProperties);

		newTextProperties.v2fStartPos = sf::Vector2f(lastColumnCoordinate, 85 + (rank * 40));
		newTextProperties.String = currentRank.sScore;
		GUI::GetInstance().CreateText(scoreKey, newTextProperties);
	}
}

void HighScores::UpdateScores()
{
	for (unsigned rank = 1; rank <= MAX_SCORES_DISPLAY; rank++)
	{
		//Load the score and name at current rank
		HighScoreEntry currentRank = m_mapScoreList.find(rank)->second;

		//Set up a unique name for each text object that makes up each that
		//is to be displayed
		std::string textKey = "Rank" + std::to_string(rank);
		std::string nameKey = "Name" + std::to_string(rank);
		std::string scoreKey = "Score" + std::to_string(rank);

		//Finally, update the text in each one
		GUI::GetInstance().SetText(textKey, std::to_string(rank));

		GUI::GetInstance().SetText(nameKey, currentRank.sName1 + "  &  " + currentRank.sName2);

		GUI::GetInstance().SetText(scoreKey, currentRank.sScore);
	}
}

void HighScores::StartInputModeOnRankEntry(unsigned _inRank)
{
	for (unsigned currentRankEdited = MAX_SCORES_DISPLAY-1; currentRankEdited >= _inRank; currentRankEdited-- )
	{
		MoveScoreDown(currentRankEdited);
	}
}

void HighScores::MoveScoreDown(unsigned _inRankToMoveDown)
{
	if (_inRankToMoveDown < MAX_SCORES_DISPLAY)
	{
		HighScoreEntry* entryToMove = &(m_mapScoreList.find(_inRankToMoveDown)->second);
		HighScoreEntry* destRank = &(m_mapScoreList.find(_inRankToMoveDown+1)->second);

		destRank->sName1 = entryToMove->sName1;
		destRank->sName2 = entryToMove->sName2;
		destRank->sScore = entryToMove->sScore;
	}
	else
	{
		//sorry will
		printf("Moving rank %i down removes it from the list", _inRankToMoveDown);
	}
}
