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
	CreateScoreDisplay();

	if (Statics::fGameScore > 0.0f)
	{
		//m_bReadOnly = true;
		unsigned currentScoreRank = CheckIfNewHighScore();
		if ( currentScoreRank > 0)
		{
			m_bReadOnly = false;
			StartInputModeOnRankEntry(currentScoreRank);
			UpdateScores();
		}
	}
}

HighScores::~HighScores()
{
	Statics::fGameScore = 0;
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
		//If not in readonly mode, then checks player key presses to determine
		//what character and which to set/change
		if(Statics::EventHandle.type == sf::Event::KeyPressed)
		{
			ParsePlayerCharacterInputs();

			//Update current score list everytime a key press is register.
			HighScoreEntry* entryToChange = &(m_mapScoreList.find(m_uNewScoreRank)->second);
			entryToChange->sName1 = std::string(m_cNameInput_P1, sizeof(m_cNameInput_P1));
			entryToChange->sName2 = std::string(m_cNameInput_P2, sizeof(m_cNameInput_P1));
			UpdateScores();

			if (m_bPlayer1_Finish && m_bPlayer2_Finish)
			{
				RecordScores();
				m_bReadOnly = true;
			}
		}
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
		//For each possible rank,check if the current score is higher than the rank's score
		//return the rank if so.
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
	dataFile.close();
}

void HighScores::RecordScores()
{
	std::ofstream dataFile;

	dataFile.open(m_ksFileLocation, std::ios::trunc);

	for (unsigned rank = 1; rank <= MAX_SCORES_DISPLAY; rank++)
	{
		//Load the score and name at current rank
		HighScoreEntry currentRank = m_mapScoreList.find(rank)->second;

		if (stoi(currentRank.sScore) > 0)
		{
			//concatenate the 2 names and the score into a single string separated by a comma
			//write that line into the file
			std::string dataLine = currentRank.sName1 + "," + currentRank.sName2 + ',' + currentRank.sScore + "\n";
			dataFile << dataLine;
		}
	}

	dataFile.close();
}

void HighScores::CreateScoreDisplay()
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
		newTextProperties.v2fStartPos = sf::Vector2f(firstColumnCoordinate, 100 + (rank * 40));
		newTextProperties.String = std::to_string(rank);
		GUI::GetInstance().CreateText(textKey, newTextProperties);

		newTextProperties.v2fStartPos = sf::Vector2f(middleColumnCoordinate, 100 + (rank * 40));
		newTextProperties.String = currentRank.sName1 + "  &  " + currentRank.sName2;
		GUI::GetInstance().CreateText(nameKey, newTextProperties);

		newTextProperties.v2fStartPos = sf::Vector2f(lastColumnCoordinate, 100 + (rank * 40));
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
	m_uNewScoreRank = _inRank;
	for (unsigned currentRankEdited = MAX_SCORES_DISPLAY-1; currentRankEdited >= _inRank; currentRankEdited-- )
	{
		MoveScoreDown(currentRankEdited);
	}
	for ( short index = 0; index < 3;index++)
	{
		m_cNameInput_P1[index] = 'A';
		m_cNameInput_P2[index] = 'A';
	}
	HighScoreEntry* entryToChange = &(m_mapScoreList.find(_inRank)->second);
	entryToChange->sName1 = std::string(m_cNameInput_P1, sizeof(m_cNameInput_P1));
	entryToChange->sName2 = std::string(m_cNameInput_P2, sizeof(m_cNameInput_P1));
	entryToChange->sScore = std::to_string(int(Statics::fGameScore));
}

void HighScores::ParsePlayerCharacterInputs()
{
	if (!m_bPlayer1_Finish)
	{
		//Player 1 input
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::A)
		{
			if (m_uCharIndex_P1 > 0)
			{
				m_uCharIndex_P1--;
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::D)
		{
			if (m_uCharIndex_P1 < 2)
			{
				m_uCharIndex_P1++;
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::W)
		{
			if (m_cNameInput_P1[m_uCharIndex_P1] > ' ')
			{
				m_cNameInput_P1[m_uCharIndex_P1]--;
			}
			else
			{
				m_cNameInput_P1[m_uCharIndex_P1] = 'z';
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::S)
		{
			if (m_cNameInput_P1[m_uCharIndex_P1] < 'z')
			{
				m_cNameInput_P1[m_uCharIndex_P1]++;
			}
			else
			{
				m_cNameInput_P1[m_uCharIndex_P1] = ' ';
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::B)
		{
			m_bPlayer1_Finish = true;
		}
	}
	else
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::V ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::B)
		{
			m_bPlayer1_Finish = false;
		}
	}

	if (!m_bPlayer2_Finish)
	{
		//Player 2 Input
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Left)
		{
			if (m_uCharIndex_P2 > 0)
			{
				m_uCharIndex_P2--;
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Right)
		{
			if (m_uCharIndex_P2 < 2)
			{
				m_uCharIndex_P2++;
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Up)
		{
			if (m_cNameInput_P2[m_uCharIndex_P2] > ' ')
			{
				m_cNameInput_P2[m_uCharIndex_P2]--;
			}
			else
			{
				m_cNameInput_P2[m_uCharIndex_P2] = 'z';
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Down)
		{
			if (m_cNameInput_P2[m_uCharIndex_P2] < 'z')
			{
				m_cNameInput_P2[m_uCharIndex_P2]++;
			}
			else
			{
				m_cNameInput_P2[m_uCharIndex_P2] = ' ';
			}
		}

		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1 ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad2)
		{
			m_bPlayer2_Finish = true;
		}
	}
	else
	{
		if (Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad1 ||
			Statics::EventHandle.key.code == sf::Keyboard::Key::Numpad2)
		{
			m_bPlayer2_Finish = false;
		}
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

