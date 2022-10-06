// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Statics.h 
// Description : Statics Header File
// Author : Inman, Will

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

enum class ELEMENTTYPE
{
	NONE,
	FIRE,
	WATER,
	EARTH,
};

enum class PICKUPTYPE
{
	UNASSIGNED = 0,

	HEALTH,
	MANA
};

enum class OBSTACLETYPE
{
	ROCK,
	HEDGE,
	LOG
};

enum class PROJECTILETYPE
{
	BASIC,
	SECONDARY,
	ARROW
};

struct ProjectileProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fScale{ 1,1 };
	bool bFriendly{ true };
	unsigned uDamage{ 0 };
	float fMoveSpeed{ 1000.0f };
	unsigned uNumberOfFrames{ 1 };
	ELEMENTTYPE Element{ ELEMENTTYPE::NONE };
	bool bDestroyOnCollision{ true };
	bool bApplyElementToTarget{ false };
	PROJECTILETYPE eProjectileType{ PROJECTILETYPE::BASIC };
};

struct ObstacleProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fScale{ 1,1 };
	OBSTACLETYPE ObstacleType{ OBSTACLETYPE::ROCK };
	sf::Vector2f v2fBoxColliderSize{ 10,10 };
	float fBoxColliderOffsetY{};	
	float fMoveSpeed{ 160.0f };
};

struct PlayerProperties
{
	//sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fBoxColliderSize{ 10,10 };
	float fBoxColliderOffsetY{};
	float fMoveSpeed{ 1000.0f };
	int iMaxHealth{ 3 };
	int iMaxMana{ 3 };
	bool bPlayerOne{true};
	sf::Vector2f v2fScale{ 1,1 };
};

struct EnemyProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	ENEMYTYPE EnemyType{ ENEMYTYPE::KAMIKAZE };
	sf::Vector2f v2fMoveScale{ 1.0f,1.0f };
	sf::Vector2f v2fJumpScale{ 1.2f,1.2f };
	float fMoveSpeed{ 200.0f };
	float fJumpSpeed{ 300.0f };
	int iMaxHealth{ 3 };
};

struct ButtonProperties
{
	std::string Label{};
	sf::Vector2f v2fStartPos{};
	std::function<void()> OnPressFunction{nullptr};
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fScale{ 1,1 };
};

struct TextProperties
{
	sf::Vector2f v2fStartPos{};
	std::string String{};
	sf::Color Color {sf::Color::Black};
	int iCharacterSize{36};
	sf::Color OutlineColor{ sf::Color::Black };
};

struct ImageProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fScale{ 1,1 };
};

struct SpecialEffectProperties
{
	sf::Texture* Texture{ nullptr };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fScale{ 1,1 };
	sf::Color Color{1,1,1};
	unsigned uNumberOfFrames{ 1 };
	float fAnimFrameInterval{};
	sf::Vector2f v2fVelocity{};
};

struct AnimStateProperties
{
	sf::Texture* StateTexture{ nullptr };
	sf::Vector2i TopLeftStartFrame { 0,0 };
	int iFrameHeight{ 32 };
	int iFrameWidth{ 32 };
	unsigned uNumberOfFrames{ 1 };
	float fFrameInterval{};
	sf::Vector2f v2fScale{ 1.0f,1.0f };
	bool bLoops{ false };
};

struct PickupProperties
{
	PICKUPTYPE ePickupType{ PICKUPTYPE ::UNASSIGNED };
	sf::Vector2f v2fStartPos{};
	sf::Vector2f v2fVelocity{};
	sf::Vector2f v2fScale{};
	unsigned uNumberOfFrames{ 1 };
	float fAnimFrameInterval{};
};

class Statics
{
public:
	static sf::RenderWindow RenderWindow;
	static sf::Event EventHandle;
	static sf::Font MetalMania;
	static void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);
	static void InitGlobalFont(std::string _fileName);

	static sf::Clock Time;
	static float fTimeScale;
	static float fDeltaTime;
	static float fUnscaledDeltaTime;
	static void CalculateDeltaTime();
	static void SetPaused(bool _paused);
	static bool IsPaused();

	static float fGameScore;

	static float fBackgroundScrollSpeed;

	static bool bDebugMode;

private:
	static float m_fLastTime;

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

