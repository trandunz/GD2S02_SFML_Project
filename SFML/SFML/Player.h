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
	Player(PlayerProperties _properties);
	~Player();

	void HandleEvents();
	void Update();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f _newPosition);

	sf::Sprite GetSprite() const;

	void TakeDamage(unsigned _amount);
	void Heal(unsigned _amount);

	bool CheckCollision(BoxCollider& _otherCollider);

	bool bDestroy{ false };
	
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	sf::Vector2f GetMoveInput();
	void SetHPMax();
	void SetManaMax();
	void UpdateGUI();

	void CreateHeartsUI(std::string _prefix, sf::Vector2f _heartPos1, sf::Vector2f _heartPos2, sf::Vector2f _heartPos3);
	void CreateManaUI(std::string _prefix, sf::Vector2f _potPos1, sf::Vector2f _potPos2, sf::Vector2f _potPos3);
	void UpdateHeartsUI(std::string _prefix);
	void UpdateManaUI(std::string _prefix);

	void CreateSpecialVFX();
	void SetP1SpecialVFXPosition(sf::Vector2f _position);
	void SetP2SpecialVFXPosition(sf::Vector2f _position);

	void BasicAttack();
	void SecondaryAttack();
	void Special();

	sf::Vector2f GetFuturePosition(sf::Vector2f _velocity) const;
	void RestrictToScreen();

	ProjectileProperties m_BasicAttackProperties{};
	ProjectileProperties m_SecondaryAttackProperties{};
	PlayerProperties m_Properties{};
	float m_AttackSpeed{ 0.2f };
	float m_SpecialDuration{ 10.0f };
	float m_CombineSpecialDelay{ 0.5f };
	float m_SpecialTimer{ };
	float m_AttackTimer{ };
	bool m_bCollided{ false };
	sf::Sprite m_Mesh{};
	sf::Vector2f m_PreviousMove{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
	int m_iCurrentMana{};

	BoxCollider* m_BoxCollider{nullptr};
	float fColliderOffset{};

	sf::Keyboard::Key m_MoveUpKey {sf::Keyboard::W };
	sf::Keyboard::Key m_MoveDownKey { sf::Keyboard::S};
	sf::Keyboard::Key m_MoveLeftKey {sf::Keyboard::A };
	sf::Keyboard::Key m_MoveRightKey {sf::Keyboard::D };
	sf::Keyboard::Key m_BasicAttackKey {sf::Keyboard::V };
	sf::Keyboard::Key m_SecondaryAttackKey {sf::Keyboard::B };
	sf::Keyboard::Key m_SpecialAttackKey {sf::Keyboard::N };

public:
	BoxCollider* GetCollisionBox();

	int GetCurrentHealth() const;
};

