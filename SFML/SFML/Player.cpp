#include "Player.h"
#include "GUI.h"
#include "PlayerManager.h"
#include "VFX.h"
#include "ProjectileManager.h"
#include "Math.h"
#include "TextureLoader.h"

Player::Player(PlayerProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	SetOriginCenter(m_Mesh);
	m_Properties = _properties;
	SetHPMax();
	SetManaMax();

	if (m_Properties.bPlayerOne == false)
	{
		m_MoveUpKey = sf::Keyboard::Up;
		m_MoveDownKey = sf::Keyboard::Down;
		m_MoveLeftKey = sf::Keyboard::Left;
		m_MoveRightKey = sf::Keyboard::Right;
		m_BasicAttackKey = sf::Keyboard::Numpad1;
		m_SecondaryAttackKey = sf::Keyboard::Numpad2;
		m_SpecialAttackKey = sf::Keyboard::Numpad3;

		CreateHeartsUI("P2", { 704, 40 }, { 736,40 }, { 768,40 });
		CreateManaUI("P2", { 704, 80 }, { 736, 80 }, { 768, 80 });

		m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Fire_Spell_Animated.png");// ("Fire_Spell.png");
		m_BasicAttackProperties.Scale = { 2.00f,2.00f };

		m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Fire_Spell_Animated.png");// ("Fire_Spell.png");
		m_SecondaryAttackProperties.Scale = { 2.00f,2.00f };
	}
	else
	{
		CreateHeartsUI("P1", { 16, 40 }, { 48,40 }, { 80,40 });
		CreateManaUI("P1", { 16, 80 }, { 48, 80 }, { 80, 80 });

		m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Earth_Spell_Animated.png");//("Earth_Spell.png");
		m_BasicAttackProperties.Scale = { 2.00f,2.00f };

		m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Earth_Spell_Animated.png");//("Earth_Spell.png");
		m_SecondaryAttackProperties.Scale = { 2.00f,2.00f };
	}

	CreateSpecialVFX();
}

Player::~Player()
{
	if (m_Properties.bPlayerOne)
	{

		VFX::GetInstance().StopEffect("P1_P1Special");
		VFX::GetInstance().StopEffect("P1_P2Special");
	}
	else
	{
		VFX::GetInstance().StopEffect("P2_P1Special");
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
		if (m_AttackTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
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

	m_v2fVelocity = GetMoveInput();
	m_PreviousMove = m_Mesh.getPosition();
	if (Magnitude(m_v2fVelocity) > 0)
	{
		m_Mesh.move(m_v2fVelocity * m_Properties.fMoveSpeed * Statics::fDeltaTime);
	}
	RestrictToScreen();
	UpdateGUI();
}
	

void Player::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
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
	VFX::GetInstance().GetEffect("P1_P1Special").setPosition(_position + sf::Vector2f{10, -40 });
	VFX::GetInstance().GetEffect("P2_P1Special").setPosition(_position - sf::Vector2f{ 10, 40 });
}

void Player::SetP2SpecialVFXPosition(sf::Vector2f _position)
{
	VFX::GetInstance().GetEffect("P1_P2Special").setPosition(_position + sf::Vector2f{ 10, -40 });
	VFX::GetInstance().GetEffect("P2_P2Special").setPosition(_position - sf::Vector2f{ 10, 40 });
}

void Player::BasicAttack()
{
	m_BasicAttackProperties.StartPos = GetPosition(); // Get player position
	ProjectileManager::GetInstance().CreateProjectile(m_BasicAttackProperties);
}

void Player::SecondaryAttack()
{
	if (m_iCurrentMana >= 1)
	{
		m_iCurrentMana--;
		// Spawn Secondary Projectile
		m_SecondaryAttackProperties.StartPos = GetPosition(); // Get player position
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
		}
		else
		{
			VFX::GetInstance().PlayEffect("P2_P1Special", m_SpecialDuration);
			VFX::GetInstance().PlayEffect("P2_P2Special", m_SpecialDuration);
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
		Destroy = true;
	}
}

void Player::Heal(unsigned _amount)
{
	for (short i = _amount; m_iCurrentHealth < m_Properties.iMaxHealth; i--)
	{
		m_iCurrentHealth++;
	}
}

bool Player::CheckCollision(sf::Sprite _otherSprite)
{
	if (m_Mesh.getGlobalBounds().intersects(_otherSprite.getGlobalBounds()))
	{
		if (_otherSprite.getPosition().y + (_otherSprite.getScale().y / 2.0f) < m_PreviousMove.y - 32.0f)
		{
			m_Mesh.setPosition(m_PreviousMove + sf::Vector2f(0, 1.0f));
		}
		else
		{
			m_Mesh.setPosition(m_PreviousMove);
		}


		
		return true;
	}
	return false;
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


