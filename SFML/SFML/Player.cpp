// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Player.cpp 
// Description : Player Implementation File		
// Author : Inman, Will

#include "Player.h"
#include "GUI.h"
#include "PlayerManager.h"
#include "VFX.h"
#include "ProjectileManager.h"
#include "Math.h"
#include "TextureLoader.h"
#include "BoxCollider.h"

Player::Player(PlayerProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetPosition(_properties.v2fStartPos);
	m_Mesh.setScale(_properties.v2fScale);
	SetOriginCenter(m_Mesh);
	m_Properties = _properties;
	SetHPMax();
	SetManaMax();

	// Set box collider
	fColliderOffset = _properties.fBoxColliderOffsetY;
	m_BoxCollider = new BoxCollider(_properties.v2fBoxColliderSize, sf::Vector2f(m_Mesh.getPosition().x, m_Mesh.getPosition().y + fColliderOffset));

	//Set up properties that are the same for both players
	m_BasicAttackProperties.uDamage = 1;
	m_SecondaryAttackProperties.bDestroyOnCollision = false;
	m_SecondaryAttackProperties.fMoveSpeed = 500.0f;

	if (m_Properties.bPlayerOne == false)
	{
		m_MoveUpKey = sf::Keyboard::Key::Up;
		m_MoveDownKey = sf::Keyboard::Key::Down;
		m_MoveLeftKey = sf::Keyboard::Key::Left;
		m_MoveRightKey = sf::Keyboard::Key::Right;
		m_BasicAttackKey = sf::Keyboard::Key::Numpad1;
		m_SecondaryAttackKey = sf::Keyboard::Key::Numpad2;
		m_SpecialAttackKey = sf::Keyboard::Key::Numpad3;

		sf::Vector2u windowSize = Statics::RenderWindow.getSize();
		CreateHeartsUI("P2", { windowSize.x - 80.0f, 40 }, { windowSize.x - 48.0f ,40 }, { windowSize.x - 16.0f,40 });
		CreateManaUI("P2", { windowSize.x - 80.0f, 80 }, { windowSize.x - 48.0f, 80 }, { windowSize.x - 16.0f, 80 });

		m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Fire_Spell_Animated.png");// ("Fire_Spell.png");
		m_BasicAttackProperties.v2fScale = { 2.00f,2.00f };
		m_BasicAttackProperties.uNumberOfFrames = 3;

		m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Fire_Spell_Animated.png");// ("Fire_Spell.png");
		m_SecondaryAttackProperties.v2fScale = { 2.00f,2.00f };
		m_SecondaryAttackProperties.uNumberOfFrames = 3;
		m_SecondaryAttackProperties.Element = ELEMENTTYPE::FIRE;
	}
	else
	{
		CreateHeartsUI("P1", { 16, 40 }, { 48,40 }, { 80,40 });
		CreateManaUI("P1", { 16, 80 }, { 48, 80 }, { 80, 80 });

		m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Earth_Spell_Animated.png");//("Earth_Spell.png");
		m_BasicAttackProperties.v2fScale = { 2.00f,2.00f };
		m_BasicAttackProperties.uNumberOfFrames = 3;

		m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/SecondaryDefault_Green.png");//("Earth_Spell.png");
		m_SecondaryAttackProperties.v2fScale = { 1.5f,1.5f };
		m_SecondaryAttackProperties.uNumberOfFrames = 1;
		m_SecondaryAttackProperties.Element = ELEMENTTYPE::EARTH;
	}

	CreateSpecialVFX();
}

Player::~Player()
{
	if (m_Properties.bPlayerOne)
	{

		VFX::GetInstance().StopEffect("P1_P1Special");
		VFX::GetInstance().StopEffect("P2_P1Special");
	}
	else
	{
		VFX::GetInstance().StopEffect("P1_P2Special");
		VFX::GetInstance().StopEffect("P2_P2Special");
	}
}

void Player::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::KeyPressed
		&& Statics::EventHandle.key.code == m_BasicAttackKey)
	{
	}
}

void Player::Update()
{
	m_AttackTimer -= Statics::fDeltaTime;
	if (sf::Keyboard::isKeyPressed(m_SpecialAttackKey))
	{
		if (m_AttackTimer <= 0 && m_SpecialTimer <= 0)
		{
			m_SpecialTimer = m_SpecialDuration;
			m_AttackTimer = m_AttackSpeed;
			Special();
		}
	}
	if (sf::Keyboard::isKeyPressed(m_SecondaryAttackKey))
	{
		if (m_AttackTimer <= 0 && m_SecondaryTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
			m_SecondaryTimer = m_SecondaryCooldown;
			SecondaryAttack();
		}
	}
	if (sf::Keyboard::isKeyPressed(m_BasicAttackKey))
	{ 
		if (m_AttackTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
			BasicAttack();
		}
	}

	if (m_SpecialTimer > 0)
	{
		m_SpecialTimer -= Statics::fDeltaTime;
	}

	if (m_SecondaryTimer > 0)
	{
		m_SecondaryTimer -= Statics::fDeltaTime;
	}

	m_v2fVelocity = GetMoveInput();
	m_PreviousMove = m_Mesh.getPosition();
	if (Magnitude(m_v2fVelocity) > 0)
	{
		m_Mesh.move(m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
	}
	RestrictToScreen();
	UpdateGUI();

	// Update position of collider
	if (m_BoxCollider)
		m_BoxCollider->SetPosition({ m_Mesh.getPosition().x, m_Mesh.getPosition().y + fColliderOffset });
}
	

void Player::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);

	// Draw box collider if debug mode turned on
	if (m_BoxCollider)
		m_BoxCollider->DrawDebug(_target);
}

sf::Vector2f Player::GetMoveInput()
{
	sf::Vector2f input{};

	if (sf::Keyboard::isKeyPressed(m_MoveUpKey))
		input.y -= 1;
	if (sf::Keyboard::isKeyPressed(m_MoveDownKey))
		input.y += 1;
	if (sf::Keyboard::isKeyPressed(m_MoveRightKey))
		input.x += 1;
	if (sf::Keyboard::isKeyPressed(m_MoveLeftKey))
		input.x -= 1;

	return Normalize(input);
}

void Player::SetHPMax()
{
	m_iCurrentHealth = m_Properties.iMaxHealth;
}

void Player::SetManaMax()
{
	m_iCurrentMana = m_Properties.iMaxMana;
}

void Player::UpdateGUI()
{
	if (m_Properties.bPlayerOne)
	{
		UpdateHeartsUI("P1");
		UpdateManaUI("P1");
		SetP1SpecialVFXPosition(GetPosition());
	}
	else
	{
		UpdateHeartsUI("P2");
		UpdateManaUI("P2");
		SetP2SpecialVFXPosition(GetPosition());
	}
}

void Player::CreateHeartsUI(std::string _prefix, sf::Vector2f _heartPos1, sf::Vector2f _heartPos2, sf::Vector2f _heartPos3)
{
	GUI::GetInstance().CreateImage(_prefix + "_HP1",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			_heartPos1,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_HP2",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			_heartPos2,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_HP3",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			_heartPos3,
			{0.5f, 0.5f}
		}
	);
}

void Player::CreateManaUI(std::string _prefix, sf::Vector2f _potPos1, sf::Vector2f _potPos2, sf::Vector2f _potPos3)
{
	GUI::GetInstance().CreateImage(_prefix + "_AP1",
		{
			&TextureLoader::LoadTexture("FullMana.png"),
			_potPos1,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_AP2",
		{
			&TextureLoader::LoadTexture("FullMana.png"),
			_potPos2,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_AP3",
		{
			&TextureLoader::LoadTexture("FullMana.png"),
			_potPos3,
			{0.5f, 0.5f}
		}
	);
}

void Player::UpdateHeartsUI(std::string _prefix)
{
	if (m_iCurrentHealth >= 1)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP1", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP1", TextureLoader::LoadTexture("EmptyHeart.png"));

	if (m_iCurrentHealth >= 2)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP2", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP2", TextureLoader::LoadTexture("EmptyHeart.png"));

	if (m_iCurrentHealth >= 3)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP3", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP3", TextureLoader::LoadTexture("EmptyHeart.png"));
}

void Player::UpdateManaUI(std::string _prefix)
{
	if (m_iCurrentMana >= 1)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP1", TextureLoader::LoadTexture("FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP1", TextureLoader::LoadTexture("EmptyMana.png"));

	if (m_iCurrentMana >= 2)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP2", TextureLoader::LoadTexture("FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP2", TextureLoader::LoadTexture("EmptyMana.png"));

	if (m_iCurrentMana >= 3)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP3", TextureLoader::LoadTexture("FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP3", TextureLoader::LoadTexture("EmptyMana.png"));
}

void Player::CreateSpecialVFX()
{
	if (m_Properties.bPlayerOne)
	{
		VFX::GetInstance().CreateEffect("P1_P1Special",
			{
				&TextureLoader::LoadTexture("SpecialEffect_Temp.png"),
				{0,0},
				{ 0.25f,0.25f },
				{0,255,0}
			});
		VFX::GetInstance().CreateEffect("P1_P2Special",
			{
				&TextureLoader::LoadTexture("SpecialEffect_Temp.png"),
				{0,0},
				{ 0.25f,0.25f },
				{0,255,0}
			});
	}
	else
	{ 
		VFX::GetInstance().CreateEffect("P2_P1Special",
			{
				&TextureLoader::LoadTexture("SpecialEffect_Temp.png"),
				{0,0},
				{ 0.25f,0.25f },
				{255,0,0}
			});
		VFX::GetInstance().CreateEffect("P2_P2Special",
			{
				&TextureLoader::LoadTexture("SpecialEffect_Temp.png"),
				{0,0},
				{ 0.25f,0.25f },
				{255,0,0}
			});
	}
}

void Player::SetP1SpecialVFXPosition(sf::Vector2f _position)
{
	VFX::GetInstance().GetEffect("P1_P1Special").SetPosition(_position + sf::Vector2f{ 10, -40 });
	VFX::GetInstance().GetEffect("P2_P1Special").SetPosition(_position - sf::Vector2f{ 10, 40 });
}

void Player::SetP2SpecialVFXPosition(sf::Vector2f _position)
{
	VFX::GetInstance().GetEffect("P1_P2Special").SetPosition(_position + sf::Vector2f{ 10, -40 });
	VFX::GetInstance().GetEffect("P2_P2Special").SetPosition(_position - sf::Vector2f{ 10, 40 });
}

void Player::BasicAttack()
{
	m_BasicAttackProperties.v2fStartPos = GetPosition(); // Get player position
	ProjectileManager::GetInstance().CreateProjectile(m_BasicAttackProperties);
}

void Player::SecondaryAttack()
{
	if (m_iCurrentMana >= 1)
	{
		m_iCurrentMana--;
		// Spawn Secondary Projectile
		m_SecondaryAttackProperties.v2fStartPos = GetPosition(); // Get player position
		ProjectileManager::GetInstance().CreateProjectile(m_SecondaryAttackProperties);
	}
}

void Player::Special()
{
	if (m_iCurrentMana >= 3)
	{
		m_iCurrentMana -= 3;
		// Spawn Special Effect
		if (m_Properties.bPlayerOne)
		{
			VFX::GetInstance().PlayEffect("P1_P1Special", m_SpecialDuration);
			VFX::GetInstance().PlayEffect("P1_P2Special", m_SpecialDuration);
			if (VFX::GetInstance().GetEffectLifetime("P2_P1Special") >= m_SpecialDuration - m_CombineSpecialDelay)
			{
				PlayerManager::GetInstance().WhipeScreenFromSpecial();
			}
		}
		else
		{
			VFX::GetInstance().PlayEffect("P2_P1Special", m_SpecialDuration);
			VFX::GetInstance().PlayEffect("P2_P2Special", m_SpecialDuration);

			if (VFX::GetInstance().GetEffectLifetime("P1_P1Special") >= m_SpecialDuration - m_CombineSpecialDelay)
			{
				PlayerManager::GetInstance().WhipeScreenFromSpecial();
			}
		}
	}
}

sf::Vector2f Player::GetPosition() const
{
	return m_Mesh.getPosition();
}

void Player::SetPosition(sf::Vector2f _newPosition)
{
	m_Mesh.setPosition(_newPosition);
}

sf::Sprite Player::GetSprite() const
{
	return m_Mesh;
}

void Player::TakeDamage(unsigned _amount)
{
	m_iCurrentHealth -= _amount;

	if (m_iCurrentHealth <= 0)
	{
		bDestroy = true;
	}
}

void Player::Heal(unsigned _amount)
{
	for (short i = _amount; m_iCurrentHealth < m_Properties.iMaxHealth; i--)
	{
		m_iCurrentHealth++;
	}
}

//bool Player::CheckCollision(sf::Sprite _otherSprite)
//{
//	if (m_Mesh.getGlobalBounds().intersects(_otherSprite.getGlobalBounds()))
//	{
//		if (_otherSprite.getPosition().y + (_otherSprite.getScale().y / 2.0f) < m_PreviousMove.y - 32.0f)
//		{
//			m_Mesh.setPosition(m_PreviousMove + sf::Vector2f(0, 1.0f));
//		}
//		else
//		{
//			m_Mesh.setPosition(m_PreviousMove);
//		}
//
//
//		
//		return true;
//	}
//	return false;
//}

bool Player::CheckCollision(BoxCollider& _otherCollider)
{
	if (m_BoxCollider)
	{
		return m_BoxCollider->CheckCollision(_otherCollider);
	}
	else
	{
		return false;
	}
}

int Player::GetCurrentHealth() const
{
	return m_iCurrentHealth;
}

sf::Vector2f Player::GetFuturePosition(sf::Vector2f _velocity) const
{
	return m_Mesh.getPosition() + (m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
}

void Player::RestrictToScreen()
{
	if (m_Mesh.getPosition().y + m_Mesh.getGlobalBounds().height / 2 >= Statics::RenderWindow.getSize().y)
	{
		m_Mesh.setPosition(m_Mesh.getPosition().x, Statics::RenderWindow.getSize().y - m_Mesh.getGlobalBounds().height / 2);
	}
	if (m_Mesh.getPosition().y - m_Mesh.getGlobalBounds().height / 2 <= 0)
	{
		m_Mesh.setPosition(m_Mesh.getPosition().x, m_Mesh.getGlobalBounds().height / 2);
	}
	if (m_Mesh.getPosition().x + m_Mesh.getGlobalBounds().width / 2 >= Statics::RenderWindow.getSize().x)
	{
		m_Mesh.setPosition(Statics::RenderWindow.getSize().x - m_Mesh.getGlobalBounds().width/2, m_Mesh.getPosition().y);
	}
	if (m_Mesh.getPosition().x - m_Mesh.getGlobalBounds().width / 2 <= 0)
	{
		m_Mesh.setPosition(m_Mesh.getGlobalBounds().width / 2, m_Mesh.getPosition().y);
	}
}

BoxCollider* Player::GetCollisionBox()
{
	return m_BoxCollider;
}


