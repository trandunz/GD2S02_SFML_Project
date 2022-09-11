#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

enum class ENEMYTYPE
{
	KAMIKAZE,
	ARCHER,
	WARRIOR,
	SHAMAN
};

struct ProjectileProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	bool bFriendly{ true };
	unsigned uDamage{ 0 };
	float fMoveSpeed{ 1000.0f };
};

struct ObstacleProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	sf::Vector2f BoxColliderSize{ 10,10 };
	float fBoxColliderOffsetY{};	
	float fMoveSpeed{ 160.0f };
};

struct PlayerProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	float fMoveSpeed{ 1000.0f };
	int iMaxHealth{ 3 };
	int iMaxMana{ 3 };
	bool bPlayerOne{true};
	sf::Vector2f Scale{ 1,1 };
};

struct EnemyProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	ENEMYTYPE EnemyType{ ENEMYTYPE::KAMIKAZE };
	sf::Vector2f Scale{ 1,1 };
	float fMoveSpeed{ 200.0f };
	int iMaxHealth{ 3 };
};

struct ButtonProperties
{
	std::string Label{};
	sf::Vector2f StartPos{};
	std::function<void()> OnPressFunction{nullptr};
	sf::Texture* Texture{ nullptr };
	sf::Vector2f Scale{ 1,1 };
};

struct TextProperties
{
	sf::Vector2f StartPos{};
	std::string String{};
	sf::Color Color{};
	int iCharacterSize{36};
};

struct ImageProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
};

struct SpecialEffectProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f StartPos{};
	sf::Vector2f Scale{ 1,1 };
	sf::Color Color{1,1,1};
};

struct AnimStateProperties
{
	sf::Texture* StateTexture{ nullptr };
	sf::Vector2i TopLeftStartFrame { 0,0 };
	int FrameHeight{ 32 };
	int FrameWidth{ 32 };
	unsigned NumberOfFrames{ 1 };
	float FrameInterval{};
	sf::Vector2f Scale{ 1.0f,1.0f };
	bool Loops{ false };
};

class Statics
{
public:
	static sf::RenderWindow RenderWindow;
	static sf::Event EventHandle;
	static sf::Font TimesNewRoman;
	static void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);
	static void InitGlobalFont(std::string _fileName);

	static sf::Clock Time;
	static float fTimeScale;
	static float fDeltaTime;
	static float fUnscaledDeltaTime;
	static void CalculateDeltaTime();

	static float fGameScore;

	static bool bDebugMode;
private:
	static float m_fLastTime;
};

