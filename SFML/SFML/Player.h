// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Player.h 
// Description : Player Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class BoxCollider;
class Player : public sf::Drawable
{
public:
	/// <summary>
	/// Contruct a player with the specified properties
	/// </summary>
	/// <param name="_properties"></param>
	Player(PlayerProperties _properties);
	/// <summary>
	/// Player Destructor
	/// </summary>
	~Player();

	/// <summary>
	/// Handles all events too do with the player. e.g Input
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// Handles updating the player
	/// </summary>
	void Update();

	/// <summary>
	/// Make the player take the specified amount of damage.
	/// </summary>
	/// <param name="_amount"></param>
	void TakeDamage(unsigned _amount);

	/// <summary>
	/// Heal the player for the specified amount of health
	/// </summary>
	/// <param name="_amount"></param>
	void Heal(unsigned _amount);

	void RestoreMana(unsigned _amount);

	/// <summary>
	/// Checks collision between the player and the specified box collider
	/// </summary>
	/// <param name="_otherCollider"></param>
	/// <returns></returns>
	bool CheckCollision(BoxCollider& _otherCollider);

	void SetTextureByElement();

	bool bDestroy{ false };
	
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	
	/// <summary>
	/// Returns a 2d vector corresponding too movement input
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetMoveInput();
	/// <summary>
	/// Sets the players hp to their maxHP
	/// </summary>
	void SetHPMax();
	/// <summary>
	/// Sets the players mana to their maxMana
	/// </summary>
	void SetManaMax();
	/// <summary>
	/// Handles updating the GUIs
	/// </summary>
	void UpdateGUI();

	/// <summary>
	/// Handles creation of the HP bar UI
	/// </summary>
	/// <param name="_prefix"></param>
	/// <param name="_heartPos1"></param>
	/// <param name="_heartPos2"></param>
	/// <param name="_heartPos3"></param>
	void CreateHeartsUI(std::string _prefix, sf::Vector2f _heartPos1, sf::Vector2f _heartPos2, sf::Vector2f _heartPos3);
	
	/// <summary>
	/// Handles creation of the Mana bar UI
	/// </summary>
	/// <param name="_prefix"></param>
	/// <param name="_potPos1"></param>
	/// <param name="_potPos2"></param>
	/// <param name="_potPos3"></param>
	void CreateManaUI(std::string _prefix, sf::Vector2f _potPos1, sf::Vector2f _potPos2, sf::Vector2f _potPos3);
	
	/// <summary>
	/// Handles updating the HP bar UI
	/// </summary>
	/// <param name="_prefix"></param>
	void UpdateHeartsUI(std::string _prefix);
	/// <summary>
	/// Handles updating the Mana bar UI
	/// </summary>
	/// <param name="_prefix"></param>
	void UpdateManaUI(std::string _prefix);

	/// <summary>
	/// Creates the VFX for the special ability
	/// </summary>
	void CreateSpecialVFX();
	/// <summary>
	/// Sets the VFX positions for player ones special ability 
	/// </summary>
	/// <param name="_position"></param>
	void SetP1SpecialVFXPosition(sf::Vector2f _position);
	/// <summary>
	/// Sets the VFX positions for player twos special ability 
	/// </summary>
	/// <param name="_position"></param>
	void SetP2SpecialVFXPosition(sf::Vector2f _position);

	/// <summary>
	/// Fires the players basic attack
	/// </summary>
	void BasicAttack();
	/// <summary>
	/// Fires the players secondary attack
	/// </summary>
	void SecondaryAttack();
	/// <summary>
	/// Fires the players special attack
	/// </summary>
	void Special();
	/// <summary>
	/// Set the wizard's element to fire
	/// </summary>
	void SetElement_Fire();
	/// <summary>
	/// Set the wizard's element to water
	/// </summary>
	void SetElement_Water();
	/// <summary>
	/// Set the wizard's element to earth
	/// </summary>
	void SetElement_Earth();

	sf::Vector2f GetFuturePosition(sf::Vector2f _velocity) const;
	void RestrictToScreen();

	ProjectileProperties m_BasicAttackProperties{};
	ProjectileProperties m_EmpoweredBasicAttackProperties{};
	ProjectileProperties m_SecondaryAttackProperties{};
	PlayerProperties m_Properties{};
	ELEMENTTYPE m_eElement = ELEMENTTYPE::NONE;
	float m_AttackSpeed{ 0.2f };
	float m_SpecialDuration{ 10.0f };
	float m_CombineSpecialDelay{ 0.5f };
	float m_SpecialTimer{ };
	float m_AttackTimer{ };
	float m_SecondaryTimer{ };
	float m_SecondaryCooldown{ 5.0f };
	bool m_bCollided{ false };
	sf::Sprite m_Mesh{};
	sf::Vector2f m_PreviousMove{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
	int m_iCurrentMana{};
	bool m_bRestrictYPosition{ true };

	BoxCollider* m_BoxCollider{nullptr}; // Player  box collider
	float fColliderOffset{}; // Y Offset position for box collider

	sf::Keyboard::Key m_MoveUpKey {sf::Keyboard::Key::W };
	sf::Keyboard::Key m_MoveDownKey { sf::Keyboard::Key::S};
	sf::Keyboard::Key m_MoveLeftKey {sf::Keyboard::Key::A };
	sf::Keyboard::Key m_MoveRightKey {sf::Keyboard::Key::D };
	sf::Keyboard::Key m_BasicAttackKey {sf::Keyboard::Key::V };
	sf::Keyboard::Key m_SecondaryAttackKey {sf::Keyboard::Key::B };
	sf::Keyboard::Key m_SpecialAttackKey {sf::Keyboard::Key::N };

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	BoxCollider* GetCollisionBox();

	int GetCurrentHealth() const;

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f _newPosition);

	sf::Sprite GetSprite() const;

	sf::Vector2f GetPreviousMove() const; 
};

