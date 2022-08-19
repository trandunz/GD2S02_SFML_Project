#pragma once
#include "Statics.h"
#include "Math.h"
#include "ProjectileManager.h"

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

	bool CheckCollision(sf::Sprite _otherSprite);
	int GetCurrentHealth() const;

	bool Destroy = false;
	
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

	ProjectileProperties m_BasicAttackProperties;
	ProjectileProperties m_SecondaryAttackProperties;
	PlayerProperties m_Properties;
	float m_AttackSpeed{ 0.2f };
	float m_SpecialDuration{ 10.0f };
	float m_SpecialTimer{ 0.0f };
	float m_AttackTimer{ 0.0f };
	bool m_bCollided = false;
	sf::Sprite m_Mesh{};
	sf::Vector2f m_PreviousMove{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};
	int m_iCurrentMana{};

	sf::Keyboard::Key MoveUpKey = sf::Keyboard::W;
	sf::Keyboard::Key MoveDownKey = sf::Keyboard::S;
	sf::Keyboard::Key MoveLeftKey = sf::Keyboard::A;
	sf::Keyboard::Key MoveRightKey = sf::Keyboard::D;
	sf::Keyboard::Key BasicAttackKey = sf::Keyboard::V;
	sf::Keyboard::Key SecondaryAttackKey = sf::Keyboard::B;
	sf::Keyboard::Key SpecialAttackKey = sf::Keyboard::N;
};

