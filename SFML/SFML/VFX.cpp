#include "VFX.h"
#include "Math.h"

void VFX::CleanupElements()
{
	CleanupMap(m_Effects);
}

void VFX::Update()
{
	for (auto& effect : m_Effects)
	{
		if (effect.second.LifeTime > 0)
		{
			effect.second.Animator.Update();
			effect.second.Animator.MoveSprite(effect.second.Properties.Velocity * Statics::fDeltaTime);
			effect.second.LifeTime -= Statics::fDeltaTime;
		}
	}
}

void VFX::CreateAndPlayEffect(std::string _key, SpecialEffectProperties _properties, float _lifeTime)
{
	m_Effects.insert_or_assign(_key, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.NumberOfFrames = _properties.NumberOfFrames;
	animatorProperties.FrameInterval = _properties.AnimFrameInterval;
	animatorProperties.Scale = _properties.Scale;
	m_Effects[_key].Properties = _properties;
	m_Effects[_key].Animator.AddState("Default", animatorProperties);
	m_Effects[_key].Animator.SetPosition(_properties.StartPos);
	m_Effects[_key].Animator.StartState("Default");
	m_Effects[_key].LifeTime = _lifeTime;
}

void VFX::CreateEffect(std::string _key, SpecialEffectProperties _properties)
{
	m_Effects.insert_or_assign(_key, SpecialEffect{});
	AnimStateProperties animatorProperties{ _properties.Texture };
	animatorProperties.NumberOfFrames = _properties.NumberOfFrames;
	animatorProperties.FrameInterval = _properties.AnimFrameInterval;
	animatorProperties.Scale = _properties.Scale;
	m_Effects[_key].Properties = _properties;
	m_Effects[_key].Animator.AddState("Default", animatorProperties);
	m_Effects[_key].Animator.SetPosition(_properties.StartPos);
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
	animatorProperties.NumberOfFrames = _properties.NumberOfFrames;
	animatorProperties.FrameInterval = _properties.AnimFrameInterval;
	animatorProperties.Scale = _properties.Scale;
	m_Effects[uniqueKeyAsString].Properties = _properties;
	m_Effects[uniqueKeyAsString].Animator.AddState("Default", animatorProperties);
	m_Effects[uniqueKeyAsString].Animator.SetPosition(_properties.StartPos);
	m_Effects[uniqueKeyAsString].Animator.StartState("Default");
	m_Effects[uniqueKeyAsString].LifeTime = _lifeTime;

	if (Statics::bDebugMode)
		Print(m_Effects.size());

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
	animatorProperties.NumberOfFrames = _properties.NumberOfFrames;
	animatorProperties.FrameInterval = _properties.AnimFrameInterval;
	animatorProperties.Scale = _properties.Scale;
	m_Effects[uniqueKeyAsString].Properties = _properties;
	m_Effects[uniqueKeyAsString].Animator.AddState("Default", animatorProperties);
	m_Effects[uniqueKeyAsString].Animator.SetPosition(_properties.StartPos);
	m_Effects[uniqueKeyAsString].Animator.StartState("Default");

	if (Statics::bDebugMode)
		Print(m_Effects.size());

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
}
