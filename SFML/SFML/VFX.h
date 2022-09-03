#pragma once
#include "Statics.h"

using SpecialEffect = std::pair<float, sf::Sprite>;

class VFX : public sf::Drawable
{
public:
	inline static VFX& GetInstance()
	{
		static VFX instance;
		return instance;
	}

	void CleanupElements();
	void Update();

	void CreateAndPlayEffect(std::string _key, SpecialEffectProperties _properties, float _lifeTime);
	void CreateEffect(std::string _key, SpecialEffectProperties _properties);
	sf::Sprite& GetEffect(std::string _key);
	void PlayEffect(std::string _key, float _lifeTime);
	void StopEffect(std::string _key);
	void SetEffectSprite(std::string _key, sf::Texture& _texture);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline VFX() {}
	inline VFX(const VFX&) {}
	inline ~VFX() {}

	std::map<std::string, SpecialEffect> m_Effects{};
};

