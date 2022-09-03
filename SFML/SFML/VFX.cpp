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
		if (effect.second.first > 0)
		{
			effect.second.first -= Statics::fDeltaTime;
		}
	}
}

void VFX::CreateAndPlayEffect(std::string _key, SpecialEffectProperties _properties, float _lifeTime)
{
	m_Effects.insert_or_assign(_key, std::make_pair(float(), sf::Sprite()));
	m_Effects[_key].second.setTexture(*_properties.Texture, true);
	m_Effects[_key].second.setScale(_properties.Scale);
	SetOriginCenter(m_Effects[_key].second);
	m_Effects[_key].second.setPosition(_properties.StartPos);
	m_Effects[_key].first = _lifeTime;
}

void VFX::CreateEffect(std::string _key, SpecialEffectProperties _properties)
{
	m_Effects.insert_or_assign(_key, std::make_pair(float(), sf::Sprite()));
	m_Effects[_key].second.setTexture(*_properties.Texture, true);
	m_Effects[_key].second.setScale(_properties.Scale);
	SetOriginCenter(m_Effects[_key].second);
	m_Effects[_key].second.setPosition(_properties.StartPos);
	m_Effects[_key].second.setColor(_properties.Color);
}

sf::Sprite& VFX::GetEffect(std::string _key)
{
	return m_Effects[_key].second;
}

void VFX::PlayEffect(std::string _key, float _lifeTime)
{
	m_Effects[_key].first = _lifeTime;
}

void VFX::StopEffect(std::string _key)
{
	m_Effects[_key].first = 0.0f;
}

void VFX::SetEffectSprite(std::string _key, sf::Texture& _texture)
{
	m_Effects[_key].second.setTexture(_texture, true);
	SetOriginCenter(m_Effects[_key].second);
}

void VFX::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& effect : m_Effects)
	{
		if (effect.second.first > 0)
			_target.draw(effect.second.second);
	}
}
