#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <functional>
#include <string> 
#include "TextureLoader.h"
#include "Animater.h"

struct ProjectileProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	bool Friendly{ true };
	unsigned Damage{ 0 };
	float MoveSpeed{ 1000.0f };
};

struct ObstacleProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	float MoveSpeed{ 160.0f };
};

struct PlayerProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	float MoveSpeed{ 1000.0f };
	int MaxHealth{ 3 };
	int MaxMana{ 3 };
	bool PlayerOne{true};
	sf::Vector2f Scale{ 1,1 };
};

struct EnemyProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	float MoveSpeed{ 200.0f };
	int MaxHealth{ 3 };
};

struct ButtonProperties
{
	std::string Label{};
	sf::Vector2f StartPos{};
	std::function<void()> OnPressFunction{nullptr};
	sf::Texture* Texture = nullptr;
	sf::Vector2f Scale{ 1,1 };
};

struct TextProperties
{
	sf::Vector2f StartPos{};
	std::string String{};
	sf::Color Color{};
	int CharacterSize{36};
};

struct ImageProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
};

struct SpecialEffectProperties
{
	sf::Texture* Texture = nullptr;
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	sf::Color Color{1,1,1};
};

class Statics
{
public:
	static sf::RenderWindow RenderWindow;
	static sf::Event EventHandle;
	static sf::Font TimesNewRoman;

	static sf::Clock Time;
	static float TimeScale;
	static float DeltaTime;
	static float UnscaledDeltaTime;
	static void CalculateDeltaTime();

	static float m_fGameScore;
private:
	static float LastTime;
};

