#include "Player.h"
#include "GUI.h"

Player::Player(PlayerProperties _properties)
{
	m_Mesh.setTexture(*_properties.Texture, true);
	SetOriginCenter(m_Mesh);
	SetPosition(_properties.StartPos);
	m_Mesh.setScale(_properties.Scale);
	m_Properties = _properties;
	SetHPMax();

	GUI::GetInstance().CreateImage("HP1",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			{32,40}
		}
	);
	GUI::GetInstance().CreateImage("HP2",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			{96,40}
		}
	);
	GUI::GetInstance().CreateImage("HP3",
		{
			&TextureLoader::LoadTexture("FullHeart.png"),
			{160,40}
		}
	);

	m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Earth_Spell.png");
	m_BasicAttackProperties.Scale = { 2.00f,2.00f };

	if (m_Properties.PlayerOne == false)
	{
		MoveUpKey = sf::Keyboard::Up;
		MoveDownKey = sf::Keyboard::Down;
		MoveLeftKey = sf::Keyboard::Left;
		MoveRightKey = sf::Keyboard::Right;
		BasicAttackKey = sf::Keyboard::RShift;
	}
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
	if (sf::Keyboard::isKeyPressed(BasicAttackKey))
	{ 
		if (m_AttackTimer <= 0)
		{
			m_AttackTimer = m_AttackSpeed;
			BasicAttack();
		}
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

void Player::UpdateGUI()
{
	if (m_iCurrentHealth >= 1)
		GUI::GetInstance().SetImageSprite("HP1", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite("HP1", TextureLoader::LoadTexture("EmptyHeart.png"));

	if (m_iCurrentHealth >= 2)
		GUI::GetInstance().SetImageSprite("HP2", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite("HP2", TextureLoader::LoadTexture("EmptyHeart.png"));

	if (m_iCurrentHealth >= 3)
		GUI::GetInstance().SetImageSprite("HP3", TextureLoader::LoadTexture("FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite("HP3", TextureLoader::LoadTexture("EmptyHeart.png"));
}

void Player::BasicAttack()
{
	m_BasicAttackProperties.StartPos = GetPosition(); // Get player position
	ProjectileManager::GetInstance().CreateProjectile(m_BasicAttackProperties);
}

void Player::SecondaryAttack()
{
}

void Player::Special()
{
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


