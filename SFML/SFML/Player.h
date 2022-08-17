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
	void UpdateGUI();

	void BasicAttack();
	void SecondaryAttack();
	void Special();

	sf::Vector2f GetFuturePosition(sf::Vector2f _velocity) const;
	void RestrictToScreen();

	ProjectileProperties m_BasicAttackProperties;
	PlayerProperties m_Properties;
	float m_AttackSpeed{ 0.2f };
	float m_AttackTimer{ 0.0f };
	bool m_bCollided = false;
	sf::Sprite m_Mesh{};
	sf::Vector2f m_PreviousMove{};
	sf::Vector2f m_v2fVelocity{};
	int m_iCurrentHealth{};

	sf::Keyboard::Key MoveUpKey = sf::Keyboard::W;
	sf::Keyboard::Key MoveDownKey = sf::Keyboard::S;
	sf::Keyboard::Key MoveLeftKey = sf::Keyboard::A;
	sf::Keyboard::Key MoveRightKey = sf::Keyboard::D;
	sf::Keyboard::Key BasicAttackKey = sf::Keyboard::Space;
};

