// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Player.cpp 
// Description : Player Implementation File		
// Author : Inman, Will; Frear, Stace

#include "Player.h"
#include "GUI.h"
#include "PlayerManager.h"
#include "VFX.h"
#include "ProjectileManager.h"
#include "Math.h"
#include "TextureLoader.h"
#include "BoxCollider.h"
#include "AudioManager.h"
#include "Animator.h"

// For warrior collision bug fix
#include "Enemy.h"

Player::Player(PlayerProperties _properties)
{
	//m_Mesh.setTexture(*_properties.Texture, true);
	m_Properties = _properties;
	SetTextureByElement();
	SetPosition(_properties.v2fStartPos);
	m_Mesh->SetScale(_properties.v2fScale);
	SetHPMax();
	SetManaMax();

	m_fMoveSpeed = _properties.fMoveSpeed;
	m_fAttackSpeed = BASE_ATKSPD;

	// Set box collider
	m_fColliderOffset = _properties.fBoxColliderOffsetY;
	m_BoxCollider = new BoxCollider(_properties.v2fBoxColliderSize, sf::Vector2f(m_Mesh->GetPosition().x, m_Mesh->GetPosition().y + m_fColliderOffset));

	//Set up properties that are the same for both players
	m_BasicAttackProperties.uDamage = 1;
	
	m_SecondaryAttackProperties.bDestroyOnCollision = false;
	m_SecondaryAttackProperties.fMoveSpeed = 250.0f;
	m_SecondaryAttackProperties.bApplyElementToTarget = true;
	m_SecondaryAttackProperties.eProjectileType = PROJECTILETYPE::SECONDARY;
	
	m_EmpoweredBasicAttackProperties = m_BasicAttackProperties;
	m_EmpoweredBasicAttackProperties.bApplyElementToTarget = true;

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
	}
	else
	{
		CreateHeartsUI("P1", { 16, 40 }, { 48,40 }, { 80,40 });
		CreateManaUI("P1", { 16, 80 }, { 48, 80 }, { 80, 80 });
	}

	CreateSpecialVFX();

	// Flash hearts effect
	m_bFlashHearts = false;
	m_fMaxFlashTime = m_fInvincibleMaxTimer;
	m_fMaxFlashSpeed = 0.1f;
	m_fFlashTime = m_fMaxFlashTime;
	m_fFlashSpeed = m_fMaxFlashSpeed;
	m_warriorCollided = nullptr;
}

Player::~Player()
{
	if (m_Mesh)
		delete m_Mesh;
	m_Mesh = nullptr;

	if (m_Properties.bPlayerOne)
	{

		VFX::GetInstance().CleanupEffect("P1_P1Special");
		VFX::GetInstance().CleanupEffect("P2_P1Special");
	}
	else
	{
		VFX::GetInstance().CleanupEffect("P1_P2Special");
		VFX::GetInstance().CleanupEffect("P2_P2Special");
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

	if (m_fAttackTimer > 0)
	{
		m_fAttackTimer -= Statics::fDeltaTime;
	}

	if (m_fSpecialTimer > 0)
	{
		m_fSpecialTimer -= Statics::fDeltaTime;
	}

	if (m_fSecondaryTimer > 0)
	{
		m_fSecondaryTimer -= Statics::fDeltaTime;
	}

	// If player is hit from earth spell, then run function to slow enemy
	if (m_bSlowed)
	{
		HandleSlow();
	}
	// If player is hit from freeze spell, then run function for freezing said enemy
	if (m_bStopped)
	{
		HandleStop();
	}
	//If not frozen, then run regular key press checks
	else
	{
		if (sf::Keyboard::isKeyPressed(m_SpecialAttackKey))
		{
			if (m_fSpecialTimer <= 0 && m_iCurrentMana >= 3)
			{
				m_fSpecialTimer = m_fSpecialDuration;
				//m_fAttackTimer = m_fAttackSpeed;
				Special();
			}
			else if(!(AudioManager::GetAudioSourceStatus("CantCast") == sf::SoundSource::Status::Playing)) {
				AudioManager::PlayAudioSource("CantCast");
			}
		}
		if (sf::Keyboard::isKeyPressed(m_SecondaryAttackKey))
		{
			if (m_fSecondaryTimer <= 0 && m_iCurrentMana >= 1)
			{
				//m_fAttackTimer = m_fAttackSpeed;
				m_fSecondaryTimer = m_fSecondaryCooldown;
				SecondaryAttack();
			}
			else if (!(AudioManager::GetAudioSourceStatus("CantCast") == sf::SoundSource::Status::Playing)) {
				AudioManager::PlayAudioSource("CantCast");
			}
		}
		if (sf::Keyboard::isKeyPressed(m_BasicAttackKey))
		{ 
			if (m_fAttackTimer <= 0)
			{
				m_fAttackTimer = m_fAttackSpeed;
				BasicAttack();
				AudioManager::PlayAudioSource("Primary");
			}
		}
	}

	m_v2fVelocity = GetMoveInput();
	m_v2fPreviousMove = m_Mesh->GetPosition();
	if (Magnitude(m_v2fVelocity) > 0)
	{
		m_Mesh->MoveSprite(m_v2fVelocity * m_fMoveSpeed * Statics::fDeltaTime);
	}
	RestrictToScreen();
	UpdateGUI();

	// Check and run player respawning
	if (m_bRespawn == true)
	{
		Respawn();
	}

	// Update position of collider
	if (m_BoxCollider)
		m_BoxCollider->SetPosition({ m_Mesh->GetPosition().x, m_Mesh->GetPosition().y + m_fColliderOffset });

	// Check and run player invincibility
	if (m_bInvincible == true)
	{
		Invincibility();
	}

	if (m_bFlashHearts)
	{
		FlashHearts();
	}

	if (m_Mesh)
		m_Mesh->Update();

	CheckWarriorCollision();
}

void Player::CheckPushedOffScreenByWarrior()
{
	if (m_BoxCollider->GetCollider().getPosition().y + m_BoxCollider->GetCollider().getSize().y / 2.0f >= Statics::RenderWindow.getSize().y)
	{
		m_bRespawn = true; // Set player to respawn
	}
}

void Player::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(*m_Mesh);

	// Draw box collider if debug mode turned on
	if (m_BoxCollider)
		m_BoxCollider->DrawDebug(_target);
}

sf::Vector2f Player::GetMoveInput()
{
	sf::Vector2f input{};

	if (bStopInput == false)
	{
		if (sf::Keyboard::isKeyPressed(m_MoveUpKey))
			input.y -= 1;
		if (sf::Keyboard::isKeyPressed(m_MoveDownKey))
			input.y += 1;
		if (sf::Keyboard::isKeyPressed(m_MoveRightKey))
			input.x += 1;
		if (sf::Keyboard::isKeyPressed(m_MoveLeftKey))
			input.x -= 1;
	}

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
			&TextureLoader::LoadTexture("GUI/FullHeart.png"),
			_heartPos1,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_HP2",
		{
			&TextureLoader::LoadTexture("GUI/FullHeart.png"),
			_heartPos2,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_HP3",
		{
			&TextureLoader::LoadTexture("GUI/FullHeart.png"),
			_heartPos3,
			{0.5f, 0.5f}
		}
	);
}

void Player::CreateManaUI(std::string _prefix, sf::Vector2f _potPos1, sf::Vector2f _potPos2, sf::Vector2f _potPos3)
{
	GUI::GetInstance().CreateImage(_prefix + "_AP1",
		{
			&TextureLoader::LoadTexture("GUI/FullMana.png"),
			_potPos1,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_AP2",
		{
			&TextureLoader::LoadTexture("GUI/FullMana.png"),
			_potPos2,
			{0.5f, 0.5f}
		}
	);
	GUI::GetInstance().CreateImage(_prefix + "_AP3",
		{
			&TextureLoader::LoadTexture("GUI/FullMana.png"),
			_potPos3,
			{0.5f, 0.5f}
		}
	);
}

void Player::UpdateHeartsUI(std::string _prefix)
{
	if (m_iCurrentHealth >= 1)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP1", TextureLoader::LoadTexture("GUI/FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP1", TextureLoader::LoadTexture("GUI/EmptyHeart.png"));

	if (m_iCurrentHealth >= 2)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP2", TextureLoader::LoadTexture("GUI/FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP2", TextureLoader::LoadTexture("GUI/EmptyHeart.png"));

	if (m_iCurrentHealth >= 3)
		GUI::GetInstance().SetImageSprite(_prefix + "_HP3", TextureLoader::LoadTexture("GUI/FullHeart.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_HP3", TextureLoader::LoadTexture("GUI/EmptyHeart.png"));
}

void Player::UpdateManaUI(std::string _prefix)
{
	if (m_iCurrentMana >= 1)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP1", TextureLoader::LoadTexture("GUI/FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP1", TextureLoader::LoadTexture("GUI/EmptyMana.png"));

	if (m_iCurrentMana >= 2)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP2", TextureLoader::LoadTexture("GUI/FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP2", TextureLoader::LoadTexture("GUI/EmptyMana.png"));

	if (m_iCurrentMana >= 3)
		GUI::GetInstance().SetImageSprite(_prefix + "_AP3", TextureLoader::LoadTexture("GUI/FullMana.png"));
	else
		GUI::GetInstance().SetImageSprite(_prefix + "_AP3", TextureLoader::LoadTexture("GUI/EmptyMana.png"));
}

void Player::CreateSpecialVFX()
{
	if (m_Properties.bPlayerOne)
	{
		sf::Texture* texture{ nullptr };
		switch (PlayerManager::GetInstance().ePlayer1Element)
		{
		case ELEMENTTYPE::FIRE:
		{
			texture = &TextureLoader::LoadTexture("VFX/Fire.png");
			break;
		}
		case ELEMENTTYPE::WATER:
		{
			texture = &TextureLoader::LoadTexture("VFX/Water.png");
			break;
		}
		case ELEMENTTYPE::EARTH:
		{
			texture = &TextureLoader::LoadTexture("VFX/Earth.png");
			break;
		}
		default:
			break;
		}
		VFX::GetInstance().CreateEffect("P1_P1Special",
			{
				texture,
				{0,0},
				{ 0.25f,0.25f },
				{0,255,0}
			});
		VFX::GetInstance().CreateEffect("P1_P2Special",
			{
				texture,
				{0,0},
				{ 0.25f,0.25f },
				{0,255,0}
			});
	}
	else
	{ 
		sf::Texture* texture{ nullptr };
		switch (PlayerManager::GetInstance().ePlayer2Element)
		{
		case ELEMENTTYPE::FIRE:
		{
			texture = &TextureLoader::LoadTexture("VFX/Fire.png");
			break;
		}
		case ELEMENTTYPE::WATER:
		{
			texture = &TextureLoader::LoadTexture("VFX/Water.png");
			break;
		}
		case ELEMENTTYPE::EARTH:
		{
			texture = &TextureLoader::LoadTexture("VFX/Earth.png");
			break;
		}
		default:
			break;
		}
		VFX::GetInstance().CreateEffect("P2_P1Special",
			{
				texture,
				{0,0},
				{ 0.25f,0.25f },
				{255,0,0}
			});
		VFX::GetInstance().CreateEffect("P2_P2Special",
			{
				texture,
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
	if (!Statics::IsPaused())
	{
		float p1SpecialLifetime = VFX::GetInstance().GetEffectLifetime("P1_P1Special");
		float p2SpecialLifetime = VFX::GetInstance().GetEffectLifetime("P2_P1Special");
		if (p1SpecialLifetime > 0)
		{
			ProjectileProperties playerOneSpecial = m_EmpoweredBasicAttackProperties;
			playerOneSpecial.eElement = PlayerManager::GetInstance().ePlayer1Element;
			playerOneSpecial.v2fStartPos = GetPosition(); // Get player position
			ProjectileManager::GetInstance().CreateProjectile(playerOneSpecial);
		}
		else if (p2SpecialLifetime > 0)
		{
			ProjectileProperties playerTwoSpecial = m_EmpoweredBasicAttackProperties;
			playerTwoSpecial.eElement = PlayerManager::GetInstance().ePlayer2Element;
			playerTwoSpecial.v2fStartPos = GetPosition(); // Get player position
			ProjectileManager::GetInstance().CreateProjectile(playerTwoSpecial);
		}
		else
		{
			m_BasicAttackProperties.v2fStartPos = GetPosition(); // Get player position
			ProjectileManager::GetInstance().CreateProjectile(m_BasicAttackProperties);
		}
	}
}

void Player::SecondaryAttack()
{
	if (m_iCurrentMana >= 1 && !Statics::IsPaused())
	{
		AudioManager::PlayAudioSource("Secondary");
		//m_iCurrentMana--;
		LoseMana(1);
		// Spawn Secondary Projectile
		m_SecondaryAttackProperties.v2fStartPos = GetPosition(); // Get player position
		ProjectileManager::GetInstance().CreateProjectile(m_SecondaryAttackProperties);
	}
}

void Player::Special()
{
	if (m_iCurrentMana >= 3 && !Statics::IsPaused())
	{
		AudioManager::PlayAudioSource("Special");

		//m_iCurrentMana -= 3;
		LoseMana(3);
		
		// Spawn Special Effect
		if (m_Properties.bPlayerOne)
		{
			VFX::GetInstance().PlayEffect("P1_P1Special", m_fSpecialDuration);
			VFX::GetInstance().PlayEffect("P1_P2Special", m_fSpecialDuration);
			if (VFX::GetInstance().GetEffectLifetime("P2_P1Special") >= m_fSpecialDuration - m_fCombineSpecialDelay)
			{
				PlayerManager::GetInstance().WhipeScreenFromSpecial();
			}
		}
		else
		{
			VFX::GetInstance().PlayEffect("P2_P1Special", m_fSpecialDuration);
			VFX::GetInstance().PlayEffect("P2_P2Special", m_fSpecialDuration);

			if (VFX::GetInstance().GetEffectLifetime("P1_P1Special") >= m_fSpecialDuration - m_fCombineSpecialDelay)
			{
				PlayerManager::GetInstance().WhipeScreenFromSpecial();
			}
		}
	}
}

void Player::SetElement_Fire()
{
	m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Fire_Spell_Animated.png");// ("Fire_Spell.png");
	m_BasicAttackProperties.v2fScale = { 2.00f,2.00f };
	m_BasicAttackProperties.uNumberOfFrames = 3;
	m_BasicAttackProperties.eElement = ELEMENTTYPE::FIRE;
	m_EmpoweredBasicAttackProperties = m_BasicAttackProperties;

	m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/16_sunburn_spritesheet.png");// ("Fire_Spell.png");
	m_SecondaryAttackProperties.v2fScale = { 1.50f,1.50f };
	m_SecondaryAttackProperties.uNumberOfFrames = 61;
	m_SecondaryAttackProperties.eElement = ELEMENTTYPE::FIRE;
}

void Player::SetElement_Water()
{
	m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Water_Spell_Animated.png");//("Earth_Spell.png");
	m_BasicAttackProperties.v2fScale = { 2.00f,2.00f };
	m_BasicAttackProperties.uNumberOfFrames = 3;
	m_BasicAttackProperties.eElement = ELEMENTTYPE::WATER;
	m_EmpoweredBasicAttackProperties = m_BasicAttackProperties;

	m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/12_nebula_spritesheet.png");//("Earth_Spell.png");
	m_SecondaryAttackProperties.v2fScale = { 1.5f,1.5f };
	m_SecondaryAttackProperties.uNumberOfFrames = 61;
	m_SecondaryAttackProperties.eElement = ELEMENTTYPE::WATER;
}

void Player::SetElement_Earth()
{
	m_BasicAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/Earth_Spell_Animated.png");//("Earth_Spell.png");
	m_BasicAttackProperties.v2fScale = { 2.00f,2.00f };
	m_BasicAttackProperties.uNumberOfFrames = 3;
	m_BasicAttackProperties.eElement = ELEMENTTYPE::EARTH;
	m_EmpoweredBasicAttackProperties = m_BasicAttackProperties;

	m_SecondaryAttackProperties.Texture = &TextureLoader::LoadTexture("Projectiles/17_felspell_spritesheet.png");//("Earth_Spell.png");
	m_SecondaryAttackProperties.v2fScale = { 1.0f,1.0f };
	m_SecondaryAttackProperties.uNumberOfFrames = 91;
	m_SecondaryAttackProperties.eElement = ELEMENTTYPE::EARTH;
}

sf::Vector2f Player::GetPosition() const
{
	return m_Mesh->GetPosition();
}

void Player::SetPosition(sf::Vector2f _newPosition)
{
	m_Mesh->SetPosition(_newPosition);
}

sf::Sprite& Player::GetSprite()
{
	return m_Mesh->GetSprite();
}

sf::Vector2f Player::GetPreviousMove() const
{
	return m_v2fPreviousMove;
}

void Player::SetRestrictYPosition(bool _restrictYPosition)
{
	m_bRestrictYPosition = _restrictYPosition;
}

bool Player::HasLostMana()
{
	return m_iCurrentMana < m_Properties.iMaxMana;
}

bool Player::HasLostHP()
{
	return m_iCurrentHealth < m_Properties.iMaxHealth;
}

void Player::TakeDamage(unsigned _amount)
{
	if( !Statics::bDebugMode)
	{
		m_iCurrentHealth -= _amount;
	}

	m_bInvincible = true;

	AudioManager::PlayAudioSource("Hit");

	if (_amount > 0.0f)
	{
		// Set the hearts to flash
		m_bFlashHearts = true;
		m_bIsFlashing = true;
		m_fFlashTime = m_fMaxFlashTime;
		m_fFlashSpeed = m_fMaxFlashSpeed;
	}

	if (m_iCurrentHealth <= 0)
	{
		m_bFlashHearts = false;
		m_bIsFlashing = false;
		SetHeartColor("P1", sf::Color::White);
		SetHeartColor("P2", sf::Color::White);
		bDestroy = true;
	}
}

void Player::Heal(unsigned _amount)
{
	m_iCurrentHealth += _amount;

	if (m_iCurrentHealth > m_Properties.iMaxHealth)
		m_iCurrentHealth = m_Properties.iMaxHealth;
}

void Player::RestoreMana(unsigned _amount)
{
	m_iCurrentMana += _amount;

	if (m_iCurrentMana > m_Properties.iMaxMana)
		m_iCurrentMana = m_Properties.iMaxMana;
}

void Player::LoseMana(unsigned _amount)
{
	if (!Statics::bDebugMode)
	{
		m_iCurrentMana -= _amount;
	}
}

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

void Player::SetTextureByElement()
{
	AnimStateProperties animProperties;
	animProperties.uNumberOfFrames = 4;
	animProperties.fFrameInterval = 0.1f;
	animProperties.bLoops = true;

	if (m_Properties.bPlayerOne == true)
	{
		switch (PlayerManager::GetInstance().ePlayer1Element)
		{
		case ELEMENTTYPE::EARTH:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Earth_Mage.png");
			SetElement_Earth();
			break;
		}
		case ELEMENTTYPE::FIRE:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Fire_Mage.png");
			SetElement_Fire();
			break;
		}
		case ELEMENTTYPE::WATER:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Water_Mage.png");
			SetElement_Water();
			break;
		}
		case ELEMENTTYPE::NONE:
		{
			std::cout << "SetTextureByElement() element set to NONE.\n";
			break;
		}
		}
	}
	else {
		switch (PlayerManager::GetInstance().ePlayer2Element)
		{
		case ELEMENTTYPE::EARTH:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Earth_Mage.png");
			SetElement_Earth();
			break;
		}
		case ELEMENTTYPE::FIRE:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Fire_Mage.png");
			SetElement_Fire();
			break;
		}
		case ELEMENTTYPE::WATER:
		{
			animProperties.StateTexture = &TextureLoader::LoadTexture("Unit/Player/Water_Mage.png");
			SetElement_Water();
			break;
		}
		case ELEMENTTYPE::NONE:
		{
			std::cout << "SetTextureByElement() element set to NONE.\n";
			break;
		}
		}
	}

	if (!m_Mesh)
		m_Mesh = new Animator;
	m_Mesh->AddState("Moving", animProperties);
	m_Mesh->SetDefaultState("Moving");
	m_Mesh->StartState("Moving");
}

void Player::ApplyStop(float _seconds, sf::Color _color)
{
	// Change sprite color
	m_StoppedSpriteColor = _color;
	m_Mesh->SetColor(_color);

	m_bSpriteColorChanged = true;
	m_bStopped = true;
	m_fStopTime = _seconds;
}

void Player::HandleStop()
{
	m_Mesh->SetColor(m_StoppedSpriteColor);
	// Stop enemy movement
	m_fMoveSpeed = 0.0f;

	m_fStopTime -= Statics::fDeltaTime;

	if (m_fStopTime <= 0)
	{
		m_bStopped = false;
		m_Mesh->SetColor(sf::Color(255, 255, 255)); // Change color back to normal sprite 
		// Reset movement and jump speed
		m_fMoveSpeed = m_Properties.fMoveSpeed;
	}
}

void Player::ApplySlow(float _seconds, float _slowMovementPercentage, sf::Color _color)
{
	// Slow enemy movement by percentage
	m_fSlowMovementPercentage = _slowMovementPercentage;

	m_SlowedSpriteColor = _color; // Set damage color
	m_fSpriteChangeColorSpeed = 0.5f; // Set speed of color change
	m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
	m_bSpriteColorChanged = true;
	m_bSlowed = true;
	m_fSlowTime = _seconds;
}

void Player::HandleSlow()
{
	m_fMoveSpeed = m_Properties.fMoveSpeed * m_fSlowMovementPercentage;
	//Multiply to make it bigger. atk spd is currently time between attacks
	//and slow percentage is assumed to be a value less than 1.
	m_fAttackSpeed =  BASE_ATKSPD / m_fSlowMovementPercentage;

	// Change sprite color
	m_fSpriteChangeColorCounter -= 1 * Statics::fDeltaTime; // Count down
	if (m_fSpriteChangeColorCounter <= 0)
	{
		m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
		m_bSpriteColorChanged = !m_bSpriteColorChanged;
	}

	if (m_bSpriteColorChanged)
		m_Mesh->SetColor(m_SlowedSpriteColor);
	else
		m_Mesh->SetColor(sf::Color(255, 255, 255));

	m_fSlowTime -= Statics::fDeltaTime; // Count down

	if (m_fSlowTime <= 0)
	{
		m_bSlowed = false;
		m_Mesh->SetColor(sf::Color(255, 255, 255)); // Change color back to normal sprite 
		// Reset movement and jump speed
		m_fMoveSpeed = m_Properties.fMoveSpeed;
		m_fAttackSpeed = BASE_ATKSPD;
	}
}

void Player::CheckWarriorCollision()
{
	if (m_warriorCollided == nullptr) 
	{		
		bStopInput = false;
	}
}

int Player::GetCurrentHealth() const
{
	return m_iCurrentHealth;
}

void Player::RestrictToScreen()
{
	// Restricting player position at bottom of window
	// Unless bool is flipped from Obstacle collisions
	if (m_bRestrictYPosition)
	{
		if (m_Mesh->GetPosition().y + m_Mesh->GetGlobalBounds().height / 2 >= Statics::RenderWindow.getSize().y)
		{
			m_Mesh->SetPosition(m_Mesh->GetPosition().x, Statics::RenderWindow.getSize().y - m_Mesh->GetGlobalBounds().height / 2);
		}
	}
	// Otherwise stop player being able to move character, then set then respawn them.
	else 
	{
		if (m_BoxCollider->GetCollider().getPosition().y >= Statics::RenderWindow.getSize().y + m_BoxCollider->GetCollider().getSize().y)
		{
			m_bRespawn = true; // Set player to respawn
		}
	}

	// Restricting player position at top of window
	if (m_Mesh->GetPosition().y - m_Mesh->GetGlobalBounds().height / 2 <= 0)
	{
		m_Mesh->SetPosition(m_Mesh->GetPosition().x, m_Mesh->GetGlobalBounds().height / 2);
	}
	// Restricting player position at right side of window
	if (m_Mesh->GetPosition().x + m_Mesh->GetGlobalBounds().width / 2 >= Statics::RenderWindow.getSize().x)
	{
		m_Mesh->SetPosition(Statics::RenderWindow.getSize().x - m_Mesh->GetGlobalBounds().width/2, m_Mesh->GetPosition().y);
	}
	// Restricting player position at left side of window
	if (m_Mesh->GetPosition().x - m_Mesh->GetGlobalBounds().width / 2 <= 0)
	{
		m_Mesh->SetPosition(m_Mesh->GetGlobalBounds().width / 2, m_Mesh->GetPosition().y);
	}
}

void Player::Respawn()
{
	m_Mesh->SetPosition(m_Properties.v2fStartPos); // Reset player position to start position
	TakeDamage(1); // Take damage
	m_bRestrictYPosition = true; // Reset bool so player is locked to inside of window
	bStopInput = false; // Reset bool so player can move character again
	m_bRespawn = false; // Reset respawn bool
	m_bInvincible = true; // Set invinsibility
}

void Player::Invincibility()
{
	m_fInvincibleTimer -= Statics::fDeltaTime; // Increase timer

	// Change sprite color
	m_fSpriteChangeColorCounter -= Statics::fDeltaTime; // Count down
	if (m_fSpriteChangeColorCounter <= 0)
	{
		m_fSpriteChangeColorCounter = m_fSpriteChangeColorSpeed;
		m_bSpriteColorChanged = !m_bSpriteColorChanged;
	}
	if (m_bSpriteColorChanged)
		m_Mesh->SetColor(m_InvincibleColor);
	else
		m_Mesh->SetColor(sf::Color(255, 255, 255));

	// Turn off invincibility when timer ends
	if (m_fInvincibleTimer <= 0)
	{
		m_fInvincibleTimer = m_fInvincibleMaxTimer;
		m_bInvincible = false;
		m_bRestrictYPosition = true;
		m_Mesh->SetColor(sf::Color(255, 255, 255));
	}
}

void Player::FlashHearts()
{
	// Change sprite color
	m_fFlashSpeed -= Statics::fDeltaTime; // Count down
	if (m_fFlashSpeed <= 0.0f)
	{
		m_fFlashSpeed = m_fMaxFlashSpeed;
		m_bIsFlashing = !m_bIsFlashing;
	}

	// m_bIsFlashing is acting as a toggle switching back and forth
	// between 2 colours.
	if (m_bIsFlashing)
	{
		if (m_Properties.bPlayerOne)
		{
			SetHeartColor("P1", sf::Color::Blue);
		}
		else 
		{
			SetHeartColor("P2", sf::Color::Blue);
		}
	}
	else 
	{
		if (m_Properties.bPlayerOne)
		{
			SetHeartColor("P1", sf::Color::Red);
		}
		else
		{
			SetHeartColor("P2", sf::Color::Red);
		}
	}
	
	// Stop flashing when flash time runs out
	m_fFlashTime -= Statics::fDeltaTime;
	if (m_fFlashTime <= 0.0f)
	{
		m_bFlashHearts = false;
		m_fFlashTime = m_fMaxFlashTime;
		SetHeartColor("P1", sf::Color::White);
		SetHeartColor("P2", sf::Color::White);
	}
}

void Player::SetHeartColor(std::string _prefix, sf::Color _color)
{
	GUI::GetInstance().GetImage(_prefix + "_HP1").setColor(_color);
	GUI::GetInstance().GetImage(_prefix + "_HP2").setColor(_color);
	GUI::GetInstance().GetImage(_prefix + "_HP3").setColor(_color);
}

BoxCollider* Player::GetCollisionBox()
{
	return m_BoxCollider;
}


