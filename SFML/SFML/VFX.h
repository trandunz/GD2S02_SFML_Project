// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : VFX.h 
// Description : VFX Header File
// Author : Inman, Will

#pragma once
#include "Animator.h"

class VFX : public sf::Drawable
{
public:
	static VFX& GetInstance();

	/// <summary>
	/// Force Cleanup all VFX elements
	/// </summary>
	void CleanupElements();

	/// <summary>
	/// Updates all vfx elements
	/// </summary>
	void Update();
	
	/// <summary>
	/// Creates an effect with the given key, properties and lifetime and then starts/plays it
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	/// <param name="_lifeTime"></param>
	void CreateAndPlayEffect(std::string _key, SpecialEffectProperties _properties, float _lifeTime);

	/// <summary>
	/// Creates an effect with the given key and properties too be used later on
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	void CreateEffect(std::string _key, SpecialEffectProperties _properties);

	/// <summary>
	/// Creates an effect with a unique key, properties and lifetime and then starts/plays it.
	/// Returns the unique key
	/// </summary>
	/// <param name="_properties"></param>
	/// <param name="_lifeTime"></param>
	/// <returns></returns>
	std::string CreateAndPlayEffect(SpecialEffectProperties _properties, float _lifeTime);

	/// <summary>
	/// Creates an effect with a unique key and properties too be used later on.
	/// Returns the unique key
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_properties"></param>
	std::string CreateEffect(SpecialEffectProperties _properties);

	/// <summary>
	/// Plays the specified effect at _key with a lifetime
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_lifeTime"></param>
	void PlayEffect(std::string _key, float _lifeTime);
	/// <summary>
	/// Stops the specified effect at _key
	/// </summary>
	/// <param name="_key"></param>
	void StopEffect(std::string _key);

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

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	Animator& GetEffect(std::string _key);
	float GetEffectLifetime(std::string _key);
};

