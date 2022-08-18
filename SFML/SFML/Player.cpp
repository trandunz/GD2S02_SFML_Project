#include "Player.h"
#include "GUI.h"
#include "PlayerManager.h"

Player::Player(PlayerProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	m_Properties = _properties;
	SetHPMax();
	SetManaMax();

	m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Earth_Spell.png");
	m_BasicAttackProperties.Scale = { 2.00f,2.00f };

	m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Earth_Spell.png");
	m_SecondaryAttackProperties.Scale = { 2.00f,2.00f };

	if (m_Properties.PlayerOne == false)
	{
		MoveUpKey = sf::Keyboard::Up;
		MoveDownKey = sf::Keyboard::Down;
		MoveLeftKey = sf::Keyboard::Left;
		MoveRightKey = sf::Keyboard::Right;
		BasicAttackKey = sf::Keyboard::Numpad1;
		SecondaryAttackKey = sf::Keyboard::Numpad2;
		SpecialAttackKey = sf::Keyboard::Numpad3;

		CreateHeartsUI("P2", { 704, 40 }, { 736,40 }, { 768,40 });
		CreateManaUI("P2", { 704, 80 }, { 736, 80 }, { 768, 80 });
	}
	else
	{
		CreateHeartsUI("P1", { 16, 40 }, { 48,40 }, { 80,40 });
		CreateManaUI("P1", { 16, 80 }, { 48, 80 }, { 80, 80 });
	}

	// Temp
	CreateSpecialVFX();
	//
}

Player::~Player()
{
}

void Player::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::KeyPressed
		&& Statics::EventHandle.key.code == BasicAttackKey)
	{
	}
}

void Player::Update()
{
	m_AttackTimer -= Statics::DeltaTime;
	if (sf::Keyboard::isKeyPressed(SpecialAttackKey))
	{
		if (m_AttackTimer <= 0 && m_SpecialTimer <= 0)
		{
			m_SpecialTimer = m_SpecialDuration;
			m_AttackTimer = m_AttackSpeed;
			Special();
		}
	}
	if (sf::Keyboard::isKeyPressed(SecondaryAttackKey))
	{
		if (m_AttackTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
			SecondaryAttack();
		}
	}
	if (sf::Keyboard::isKeyPressed(BasicAttackKey))
	{ 
		if (m_AttackTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
			BasicAttack();
		}
	}

	if (m_SpecialTimer > 0)
	{
		//Temp
		Player* otherPlayer = nullptr;
		if (m_Properties.PlayerOne == true)
		{
			SetP1SpecialVFXPosition(GetPosition());

			otherPlayer = PlayerManager::GetInstance().GetPlayerFromIndex(1);
			if (otherPlayer != nullptr)
				SetP2SpecialVFXPosition(otherPlayer->GetPosition());
		}
		else
		{
			otherPlayer = PlayerManager::GetInstance().GetPlayerFromIndex(0);
			if (otherPlayer != nullptr)
				SetP1SpecialVFXPosition(otherPlayer->GetPosition());

			SetP2SpecialVFXPosition(GetPosition());
		}	
		otherPlayer = nullptr;
		//

		m_SpecialTimer -= Statics::DeltaTime;
	}

	m_v2fVelocity = GetMoveInput();
	m_PreviousMove = m_Mesh.getPosition();
	if (Magnitude(m_v2fVelocity) > 0)
	{
		m_Mesh.move(m_v2fVelocity * m_Properties.MoveSpeed * Statics::DeltaTime);
	}
	RestrictToScreen();
	UpdateGUI();
}
	

void Player::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);

	// Temp
	if (m_SpecialTimer > 0)
	{
		_target.draw(m_P1SpecialVFX);
		_target.draw(m_P2SpecialVFX);
	}
	//
}

sf::Vector2f Player::GetMoveInput()
{
	sf::Vector2f input{};

	if (sf::Keyboard::isKeyPressed(MoveUpKey))
		input.y -= 1;
	if (sf::Keyboard::isKeyPressed(MoveDownKey))
		input.y += 1;
	if (sf::Keyboard::isKeyPressed(MoveRightKey))
		input.x += 1;
	if (sf::Keyboard::isKeyPressed(MoveLeftKey))
		input.x -= 1;

	return Normalize(input);
}

void Player::SetHPMax()
{
	m_iCurrentHealth = m_Properties.MaxHealth;
}

void Player::SetManaMax()
{
	m_iCurrentMana = m_Properties.MaxMana;
}

void Player::UpdateGUI()
{
	if (m_Properties.PlayerOne == false)
	{
		UpdateHeartsUI("P2");
		UpdateManaUI("P2");
	}
	else
	{
		UpdateHeartsUI("P1");
		UpdateManaUI("P1");
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
	m_P1SpecialVFX.setTexture(TextureLoader::LoadTexture("SpecialEffect_Temp.png"));
	SetOriginCenter(m_P1SpecialVFX);
	m_P1SpecialVFX.setScale({ 2.0f,2.0f });
	m_P2SpecialVFX.setTexture(TextureLoader::LoadTexture("SpecialEffect_Temp.png"));
	SetOriginCenter(m_P2SpecialVFX);
	m_P2SpecialVFX.setScale({ 2.0f,2.0f });
}

void Player::SetP1SpecialVFXPosition(sf::Vector2f _position)
{
	m_P1SpecialVFX.setPosition(_position);
}

void Player::SetP2SpecialVFXPosition(sf::Vector2f _position)
{
	m_P2SpecialVFX.setPosition(_position);
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
	for (short i = _amount; m_iCurrentHealth < m_Properties.MaxHealth; i--)
	{
		m_iCurrentHealth++;
	}
}

bool Player::CheckCollision(sf::Sprite _otherSprite)
{
	if (m_Mesh.getGlobalBounds().intersects(_otherSprite.getGlobalBounds()))
	{
		m_Mesh.setPosition(m_PreviousMove);
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
	return m_Mesh.getPosition() + (m_v2fVelocity * m_Properties.MoveSpeed * Statics::DeltaTime);
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


