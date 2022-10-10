// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : VFX.cpp 
// Description : VFX Implementation File		
// Author : Inman, Will

#include "VFX.h"
#include "Math.h"

VFX& VFX::GetInstance()
{
	static VFX instance;
	return instance;
}

void VFX::CleanupElements()
{
	CleanupMap(m_Effects);
	CleanupMap(m_TextEffects);
}

void VFX::Update()
{
	for (auto& effect : m_Effects)
	{
		if (effect.second.LifeTime > 0)
		{
			effect.second.Animator.Update();
			effect.second.Animator.MoveSprite(effect.second.Properties.v2fVelocity * Statics::fDeltaTime);
			effect.second.LifeTime -= Statics::fDeltaTime;
		}
	}

	for (auto& effect : m_TextEffects)
	{
		if (effect.second.LifeTime > 0)
		{
			auto& velocity = effect.second.Properties.v2fVelocity;
			auto& position = effect.second.TextLabel.getPosition();
			if (Magnitude(velocity) > 0.01f)
			{
				effect.second.TextLabel.setPosition(position + velocity * Statics::fDeltaTime);
			}
			effect.second.LifeTime -= Statics::fDeltaTime;
		}
	}
}

void VFX::CreateAndPlayEffect(std::string _key, SpecialEffectProperties _properties, float _lifeTime)
{
	m_Effects.insert_or_assign(_key, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animatorProperties.fFrameInterval = _properties.fAnimFrameInterval;
	animatorProperties.v2fScale = _properties.v2fScale;
	m_Effects[_key].Properties = _properties;
	m_Effects[_key].Animator.AddState("Default", animatorProperties);
	m_Effects[_key].Animator.SetPosition(_properties.v2fStartPos);
	m_Effects[_key].Animator.StartState("Default");
	m_Effects[_key].LifeTime = _lifeTime;
}

void VFX::CreateEffect(std::string _key, SpecialEffectProperties _properties)
{
	m_Effects.insert_or_assign(_key, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animatorProperties.fFrameInterval = _properties.fAnimFrameInterval;
	animatorProperties.v2fScale = _properties.v2fScale;
	m_Effects[_key].Properties = _properties;
	m_Effects[_key].Animator.AddState("Default", animatorProperties);
	m_Effects[_key].Animator.SetPosition(_properties.v2fStartPos);
	m_Effects[_key].Animator.StartState("Default");
}

std::string VFX::CreateAndPlayEffect(SpecialEffectProperties _properties, float _lifeTime)
{
	int uniqueKey{};
	auto it = m_Effects.find(std::to_string(uniqueKey));
	while (it != m_Effects.end())
	{
		if (it->second.LifeTime <= 0.0f)
			break;
		else
			it = m_Effects.find(std::to_string(++uniqueKey));
	}
	std::string uniqueKeyAsString = std::to_string(uniqueKey);

	m_Effects.insert_or_assign(uniqueKeyAsString, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animatorProperties.fFrameInterval = _properties.fAnimFrameInterval;
	animatorProperties.v2fScale = _properties.v2fScale;
	m_Effects[uniqueKeyAsString].Properties = _properties;
	m_Effects[uniqueKeyAsString].Animator.AddState("Default", animatorProperties);
	m_Effects[uniqueKeyAsString].Animator.SetPosition(_properties.v2fStartPos);
	m_Effects[uniqueKeyAsString].Animator.StartState("Default");
	m_Effects[uniqueKeyAsString].LifeTime = _lifeTime;

	return uniqueKeyAsString;
}

std::string VFX::CreateAndPlayTextEffect(TextEffectProperties _properties, float _lifeTime)
{
	int uniqueKey{};
	auto it = m_TextEffects.find(std::to_string(uniqueKey));
	while (it != m_TextEffects.end())
	{
		if (it->second.LifeTime <= 0.0f)
			break;
		else
			it = m_TextEffects.find(std::to_string(++uniqueKey));
	}
	std::string uniqueKeyAsString = std::to_string(uniqueKey);

	m_TextEffects.insert_or_assign(uniqueKeyAsString, TextEffect{});
	m_TextEffects[uniqueKeyAsString].Properties = _properties;
	m_TextEffects[uniqueKeyAsString].TextLabel.setCharacterSize(_properties.iCharacterSize);
	m_TextEffects[uniqueKeyAsString].TextLabel.setFillColor(_properties.Color);
	m_TextEffects[uniqueKeyAsString].TextLabel.setString(_properties.String);
	m_TextEffects[uniqueKeyAsString].TextLabel.setFont(Statics::MetalMania);
	m_TextEffects[uniqueKeyAsString].TextLabel.setPosition(_properties.v2fStartPos);
	if (_properties.OutlineColor != _properties.Color)
	{
		m_TextEffects[uniqueKeyAsString].TextLabel.setOutlineColor(_properties.OutlineColor);
		m_TextEffects[uniqueKeyAsString].TextLabel.setOutlineThickness(2.0f);
	}
	SetOriginCenter(m_TextEffects[uniqueKeyAsString].TextLabel);
	m_TextEffects[uniqueKeyAsString].LifeTime = _lifeTime;

	return uniqueKeyAsString;
}

std::string VFX::CreateEffect(SpecialEffectProperties _properties)
{
	int uniqueKey{};
	auto it = m_Effects.find(std::to_string(uniqueKey));
	while (it != m_Effects.end())
	{
		if (it->second.LifeTime <= 0.0f)
			break;
		else
			it = m_Effects.find(std::to_string(++uniqueKey));
	}
	std::string uniqueKeyAsString = std::to_string(uniqueKey);

	m_Effects.insert_or_assign(uniqueKeyAsString, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.uNumberOfFrames = _properties.uNumberOfFrames;
	animatorProperties.fFrameInterval = _properties.fAnimFrameInterval;
	animatorProperties.v2fScale = _properties.v2fScale;
	m_Effects[uniqueKeyAsString].Properties = _properties;
	m_Effects[uniqueKeyAsString].Animator.AddState("Default", animatorProperties);
	m_Effects[uniqueKeyAsString].Animator.SetPosition(_properties.v2fStartPos);
	m_Effects[uniqueKeyAsString].Animator.StartState("Default");

	return uniqueKeyAsString;
}

Animator& VFX::GetEffect(std::string _key)
{
	return m_Effects[_key].Animator;
}

void VFX::PlayEffect(std::string _key, float _lifeTime)
{
	m_Effects[_key].LifeTime = _lifeTime;
}

void VFX::StopEffect(std::string _key)
{
	m_Effects[_key].LifeTime = 0.0f;
}

float VFX::GetEffectLifetime(std::string _key)
{
	auto it = m_Effects.find(_key);
	if (it != m_Effects.end())
	{
		return it->second.LifeTime;
	}
	else
	{
		return 0.0f;
	}
}

void VFX::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& effect : m_Effects)
	{
		if (effect.second.LifeTime > 0)
			_target.draw(effect.second.Animator);
	}

	for (auto& effect : m_TextEffects)
	{
		if (effect.second.LifeTime > 0)
			_target.draw(effect.second.TextLabel);
	}
}
