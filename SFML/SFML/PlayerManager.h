// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : PlayerManager.h 
// Description : PlayerManager Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class Player;
class PlayerManager : public sf::Drawable
{
public:
	inline static PlayerManager& GetInstance()
	{
		static PlayerManager instance;
		return instance;
	}

	/// <summary>
	/// Cleans up any player marked for destroy
	/// </summary>
	void CleanupDestroyed();
	/// <summary>
	/// Force cleans up all players
	/// </summary>
	void CleanupPlayers();
	/// <summary>
	/// Creates a player with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	void CreatePlayer(PlayerProperties _properties);
	/// <summary>
	/// Handles all key and mouse events
	/// </summary>
	void HandleEvents();
	/// <summary>
	/// Player update
	/// </summary>
	void Update();

	/// <summary>
	/// Create the screen wipe vfx
	/// </summary>
	void WhipeScreenFromSpecial();

	ELEMENTTYPE ePlayer1Element{ ELEMENTTYPE::NONE };
	ELEMENTTYPE ePlayer2Element{ ELEMENTTYPE::NONE };

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline PlayerManager() {}
	inline PlayerManager(const PlayerManager& ) {}
	inline ~PlayerManager() {}

	std::vector<Player*> m_Players{};

	bool m_bIsWhipingScreen{ false };
	float m_fScreenWhipeDuration{ 3.0f };
	std::string m_sScreenWhipeVFXKey{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	std::vector<sf::Sprite> GetPlayerSprites() const;
	std::vector<Player*>& GetPlayers();
	Player* GetPlayerFromIndex(unsigned _index);
};

