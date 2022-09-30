#pragma once
#include "Animator.h".

class Player;
class BoxCollider;
class Pickup : public sf::Drawable
{
public:
	Pickup(PickupProperties _properties);
	virtual ~Pickup();

	void Update();

	sf::Vector2f GetPosition();
	bool CheckForPickup(Player& _player);

	bool bDestroy{ false };
protected:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void SetPosition(sf::Vector2f _newPosition);
	void Move(sf::Vector2f _amount);
	void SetAnimStateTextureBasedOnType(AnimStateProperties& _animProperties);
	void GivePlayerPickupEffect(Player& _player);

	PickupProperties m_Properties{};
	Animator m_Animator{};
	BoxCollider* m_BoxCollider{nullptr};
};

