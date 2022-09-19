#pragma once
#include "Animator.h"

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

	std::string CreateAndPlayEffect(SpecialEffectProperties _properties, float _lifeTime);
	std::string CreateEffect(SpecialEffectProperties _properties);

	Animator& GetEffect(std::string _key);
	void PlayEffect(std::string _key, float _lifeTime);
	void StopEffect(std::string _key);

	float GetEffectLifetime(std::string _key);

private:
	struct SpecialEffect
	{
		float LifeTime{};
		Animator Animator{};
		SpecialEffectProperties Properties{};
	};

	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	inline VFX() {}
	inline VFX(const VFX&) {}
	inline ~VFX() {}

	std::map<std::string, SpecialEffect> m_Effects{};

};

