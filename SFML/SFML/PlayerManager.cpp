// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : PlayerManager.cpp 
// Description : PlayerManager Implementation File		
// Author : Inman, Will

#include "PlayerManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "Helper.h"
#include "EnemyManager.h"
#include "VFX.h"
#include "TextureLoader.h"
#include "Enemy.h"
#include "BoxCollider.h"
#include "AudioManager.h"

void PlayerManager::CleanupDestroyed()
{
	auto it = m_Players.begin();
	while (it != m_Players.end())
	{
		if ((*it)->bDestroy == true)
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
					enemy->bDestroy = true;
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
			player->bDestroy = true;
			AudioManager::PlayAudioSource("PlayerDeath");
		}
		else
		{
			for (auto& obstacle : ObjectManager::GetInstance().GetObstacles())
			{
				if (player->CheckCollision(*obstacle->GetCollisionBox()) == true)
				{
					// Set player position to its previous position
					player->SetPosition(player->GetPreviousMove());

					// If player is also below the obstacle
					// start pushing player downwards at same speed as background/obstacles
					if (player->GetCollisionBox()->GetCollider().getPosition().y - player->GetCollisionBox()->GetCollider().getSize().y/2
						>= obstacle->GetCollisionBox()->GetCollider().getPosition().y + (obstacle->GetCollisionBox()->GetCollider().getSize().y / 2) - 1)
					{
						player->SetPosition({ player->GetPosition().x,
							obstacle->GetCollisionBox()->GetCollider().getPosition().y + (obstacle->GetCollisionBox()->GetCollider().getSize().y / 2) +
							+(Statics::fBackgroundScrollSpeed * Statics::fDeltaTime) + 2 });
					}
				}
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

	whipeEffectProperties.v2fStartPos = Statics::RenderWindow.getView().getCenter();
	whipeEffectProperties.v2fStartPos.y += Statics::RenderWindow.getSize().y / 2.0f + whipeEffectProperties.Texture->getSize().y / 2;
	whipeEffectProperties.v2fVelocity = { 0, -Statics::fBackgroundScrollSpeed * 4.0f};

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
