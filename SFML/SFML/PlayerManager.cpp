#include "PlayerManager.h"
#include "Player.h"
#include "ObjectManager.h"

void PlayerManager::CleanupDestroyed()
{
	auto it = m_Players.begin();
	while (it != m_Players.end())
	{
		if ((*it)->Destroy == true)
		{
			if ((*it) != nullptr)
			{
				delete (*it);
				(*it) = nullptr;
			}
			it = m_Players.erase(it);
			continue;
		}
		it++;
	}
}

void PlayerManager::CleanupPlayers()
{
	for (auto& player : m_Players)
	{
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}
	}
	m_Players.clear();
	m_Players.resize(0);
}

void PlayerManager::CreatePlayer(PlayerProperties _properties)
{
	m_Players.emplace_back(new Player(_properties));
}

void PlayerManager::HandleEvents()
{
	for (auto& player : m_Players)
	{
		player->HandleEvents();
	}
}

void PlayerManager::Update()
{
	for(auto& player : m_Players)
	{
		if (player->GetCurrentHealth() <= 0)
		{
			player->Destroy = true;
		}
		else
		{
			for (auto& obstacle : ObjectManager::GetInstance().GetObstacleSprites())
			{
				player->CheckCollision(obstacle);
			}
		}
		player->Update();
	}
}

std::vector<sf::Sprite> PlayerManager::GetPlayerSprites() const
{
	std::vector<sf::Sprite> sprites{};
	for (auto& player : m_Players)
	{
		sprites.emplace_back(player->GetSprite());
	}
	return sprites;
}

std::vector<Player*>& PlayerManager::GetPlayers()
{
	return m_Players;
}

Player* PlayerManager::GetPlayerFromIndex(int _index)
{
	if (m_Players.size() > _index)
		return m_Players[_index];
	else
		return nullptr;
}

void PlayerManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& player : m_Players)
	{
		_target.draw(*player);
	}
}
