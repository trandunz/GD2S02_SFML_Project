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

	void CleanupDestroyed();
	void CleanupPlayers();
	void CreatePlayer(PlayerProperties _properties);
	void HandleEvents();
	void Update();

	std::vector<sf::Sprite> GetPlayerSprites() const;
	std::vector<Player*>& GetPlayers();
	Player* GetPlayerFromIndex(unsigned _index);

	void WhipeScreenFromSpecial();

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
};

