#include "Pickup.h"
#include "BoxCollider.h"
#include "Player.h"
#include "TextureLoader.h"

Pickup::Pickup(PickupProperties _properties)
{
	m_Properties = _properties;

	AnimStateProperties animProperties;
	SetAnimStateTextureBasedOnType(animProperties);
	animProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animProperties.fFrameInterval = _properties.fAnimFrameInterval;
	animProperties.bLoops = true;
	m_Animator.AddState("Default", animProperties);
	m_Animator.SetDefaultState("Default");
	m_Animator.SetPosition(_properties.v2fStartPos);
	m_Animator.StartState("Default");

	sf::Vector2f colliderSize{};
	colliderSize.x = m_Animator.GetLocalBounds().width;
	colliderSize.y = m_Animator.GetLocalBounds().height;
	m_BoxCollider = new BoxCollider(colliderSize, m_Animator.GetPosition());
}

Pickup::~Pickup()
{
	if (m_BoxCollider)
	{
		delete m_BoxCollider;
		m_BoxCollider = nullptr;
	}
}

void Pickup::Update()
{
	Move(m_Properties.v2fVelocity * Statics::fDeltaTime);
}

sf::Vector2f Pickup::GetPosition()
{
	return m_Animator.GetPosition();
}

bool Pickup::CheckForPickup(Player& _player)
{
	bool pickedUp{ false };

	if (m_BoxCollider && _player.GetCollisionBox())
	{
		pickedUp = m_BoxCollider->CheckCollision(*_player.GetCollisionBox());
	
		if (pickedUp)
			GivePlayerPickupEffect(_player);
	}

	return pickedUp;
}

void Pickup::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	if (Statics::bDebugMode)
		m_BoxCollider->DrawDebug(_target);

	_target.draw(m_Animator);
}

void Pickup::SetPosition(sf::Vector2f _newPosition)
{
	m_Animator.SetPosition(_newPosition);
	
	if (m_BoxCollider)
		m_BoxCollider->SetPosition(_newPosition);
}

void Pickup::Move(sf::Vector2f _amount)
{
	SetPosition(GetPosition() + _amount);
}

void Pickup::SetAnimStateTextureBasedOnType(AnimStateProperties& _animProperties)
{
	switch (m_Properties.ePickupType)
	{
	case PICKUPTYPE::HEALTH:
	{
		_animProperties.StateTexture = &TextureLoader::LoadTexture("FullHeart.png");
		break;
	}
	case PICKUPTYPE::MANA:
	{
		_animProperties.StateTexture = &TextureLoader::LoadTexture("FullMana.png");
		break;
	}
	default:
		break;
	}
}

void Pickup::GivePlayerPickupEffect(Player& _player)
{
	bDestroy = true;

	switch (m_Properties.ePickupType)
	{
	case PICKUPTYPE::HEALTH:
	{
		_player.Heal(1);
		break;
	}
	case PICKUPTYPE::MANA:
	{
		_player.RestoreMana(1);
		break;
	}
	default:
		break;
	}
}
