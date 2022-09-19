#include "PlayerManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Helper.h"
#include "EnemyManager.h"
#include "VFX.h"
#include "TextureLoader.h"
#include "Enemy.h"
#include "BoxCollider.h"

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
	CleanupVector(m_Players);
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
	if (m_bIsWhipingScreen)
	{
		if (VFX::GetInstance().GetEffectLifetime(m_sScreenWhipeVFXKey) > 0)
		{
			for (auto& enemy : EnemyManager::GetInstance().GetEnemies())
			{
				if (enemy->GetCollider()->CheckCollision(VFX::GetInstance().GetEffect(m_sScreenWhipeVFXKey).GetGlobalBounds()))
				{
					enemy->m_bDestroy = true;
				}
			}
		}
		else
		{
			m_bIsWhipingScreen = false;
		}
	}

	for(auto& player : m_Players)
	{
		if (player->GetCurrentHealth() <= 0)
		{
			player->Destroy = true;
		}
		else
		{
			//for (auto& obstacle : ObjectManager::GetInstance().GetObstacles())
			//{
			//	player->CheckCollision(*obstacle);
			//}
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

Player* PlayerManager::GetPlayerFromIndex(unsigned _index)
{
	if (m_Players.size() > _index)
		return m_Players[_index];
	else
		return nullptr;
}

void PlayerManager::WhipeScreenFromSpecial()
{
	SpecialEffectProperties whipeEffectProperties{ &TextureLoader::LoadTexture("VFX/FireWall.png") };

	whipeEffectProperties.StartPos = Statics::RenderWindow.getView().getCenter();
	whipeEffectProperties.StartPos.y += Statics::RenderWindow.getSize().y / 2.0f + whipeEffectProperties.Texture->getSize().y / 2;
	whipeEffectProperties.Velocity = { 0, -Statics::fBackgroundScrollSpeed * 4.0f};

	m_sScreenWhipeVFXKey = VFX::GetInstance().CreateAndPlayEffect(whipeEffectProperties, m_fScreenWhipeDuration);
	m_bIsWhipingScreen = true;
}

void PlayerManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& player : m_Players)
	{
		_target.draw(*player);
	}
}
