// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Animator.h 
// 
// Description :
//  General purpose file to store and animate spritesheets.
//	Stores different animations tied to string name and records
//  a state as default. Will not run without at least one state added.
//	Animations can be set to loop, otherwise it will change back to
//  Default state after displaying the last frame			
// Author : Chuang, Kee

#pragma once
#include "Statics.h"

class Animator : public sf::Drawable
{
public:
	Animator();
	~Animator();

	/// <summary>
	/// Add a new animation state.
	/// Needs a unique name and the properties associated with it
	/// </summary>
	/// <param name="_stateName"></param>
	/// <param name="_properties"></param>
	void AddState(std::string _stateName, AnimStateProperties _properties);

	/// <summary>
	/// Sets the default state that this animator
	/// will start when the current running animation
	/// has finished.
	/// Returns false with warning if no state with
	/// the specified name specified
	/// </summary>
	/// <param name="_stateName"></param>
	/// <returns></returns>
	bool SetDefaultState(std::string _stateName);

	/// <summary>
	/// Starts the animation associated with the
	/// state with the provided name. Updates the
	/// max possible left position of the sprite based
	/// on the number of frames in this animation.
	/// Returns false with warning if no state with
	/// the specified name specified
	/// </summary>
	/// <param name="_stateName"></param>
	/// <returns></returns>
	bool StartState(std::string _stateName);

	void PauseAnim() { m_bPause = true; };

	void ResumeAnim() { m_bPause = false; };

	/// <summary>
	/// Checks the time elapsed for the current frame.
	/// If past the frame interval, starts the default
	/// animation or restarts to the first frame if looping
	/// </summary>
	void Update();

	/*=========================================
	Functions to using sf::Sprite functions
	=========================================*/

	void MoveSprite( const sf::Vector2f& _offset);
	void MoveSprite( float _offsetX, float _offsetY);

	void SetSpriteColor(sf::Color _color);

private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Find the state with the given name in the map of
	/// managed animation states
	/// </summary>
	/// <param name="_stateName"></param>
	/// <returns></returns>
	bool FindState(std::string _stateName);

	std::map<std::string, AnimStateProperties> m_mapAnimationStates{};
	sf::Sprite m_Mesh{};
	sf::IntRect m_irectSpriteFrame{};
	std::string m_sCurrentState{};
	std::string m_sDefaultState{};
	float m_fAnimationProgress{};
	int m_iMaxLeftFramePos{};
	bool m_bError{ false };
	bool m_bPause{ false };

public:

	/// <summary>
	/// Returns the current frame being displayed
	/// </summary>
	/// <returns></returns>
	sf::Sprite& GetSprite() { return m_Mesh; };

	/// <summary>
	/// Passes arguments to sf::sprite GetLocalBounds function
	/// </summary>
	inline sf::FloatRect GetLocalBounds() { return m_Mesh.getLocalBounds(); };
	inline sf::FloatRect GetGlobalBounds() { return m_Mesh.getGlobalBounds(); };

	void SetScale(const sf::Vector2f& _factors);
	void SetScale(float factorX, float _factorY);

	void SetPosition(const sf::Vector2f& _position);
	void SetPosition(float _positionX, float _positionY);

	/// <summary>
	/// Get the current position of the sprite
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPosition() const { return m_Mesh.getPosition(); }
};

