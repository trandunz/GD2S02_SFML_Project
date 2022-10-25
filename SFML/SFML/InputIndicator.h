#pragma once
#include "Statics.h"
#define HEIGHTOFFSET 18

class Animator;



class InputIndicator : public sf::Drawable
{
public:
	InputIndicator(std::string _label,sf::Vector2f _position, std::string _textureLocation);
	~InputIndicator();

	void SetPosition(sf::Vector2f _position);
	void SetIndicatorChar(int _charCode);
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
	
	const sf::Vector2f m_kv2IndicatorScale = { 0.9f, 1.3f };
	
	Animator* m_pIndicator = nullptr;
	std::string m_sCharPreviewLabel_Next;
	std::string m_sCharPreviewLabel_Prev;
};