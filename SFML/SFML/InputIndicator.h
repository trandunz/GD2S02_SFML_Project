#pragma once
#include "Statics.h"
#define HEIGHTOFFSET 40

class Animator;

class InputIndicator : public sf::Drawable
{
public:
	InputIndicator(std::string _label, std::string _textureLocation, sf::Vector2f _position = { 0,0 });
	~InputIndicator();
	/// <summary>
	/// Set the position of th indicator, and by extension
	/// the 2 char previews above and below
	/// </summary>
	/// <param name="_position"></param>
	void SetPosition(sf::Vector2f _position);
	/// <summary>
	/// Set the current char highlighted by the indicator
	/// and update the chars displayed by the previews
	/// </summary>
	/// <param name="_charCode"></param>
	void SetIndicatorChar(int _charCode);
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	
	//Scale the indicator to fit the font
	//Needs to be tailored to the currently used font
	const sf::Vector2f m_kv2IndicatorScale = { 0.9f, 1.3f };
	
	Animator* m_pIndicator = nullptr;
	std::string m_sCharPreviewLabel_Next;
	std::string m_sCharPreviewLabel_Prev;

public:
	sf::Vector2f GetPosition();
};