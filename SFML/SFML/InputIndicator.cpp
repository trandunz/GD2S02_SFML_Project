#include "InputIndicator.h"
#include "TextureLoader.h"
#include "Animator.h"
#include "GUI.h"

InputIndicator::InputIndicator(std::string _label, std::string _textureLocation, sf::Vector2f _position)
{
	m_sCharPreviewLabel_Next = _label + "_Next";
	m_sCharPreviewLabel_Prev = _label + "_Prev";

	AnimStateProperties indicatorTexProp;
	indicatorTexProp.StateTexture = &TextureLoader::LoadTexture(_textureLocation);
	indicatorTexProp.bLoops = true;
	indicatorTexProp.fFrameInterval = 1.0f;
	//Scale is an attempt to scale the size to the set font size
	indicatorTexProp.v2fScale = m_kv2IndicatorScale;

	//Create the sprite for the indicator
	m_pIndicator = new Animator();
	m_pIndicator->AddState("Default", indicatorTexProp);
	m_pIndicator->SetDefaultState("Default");
	//Start anims to get the sprites displayed
	m_pIndicator->StartState("Default");
	m_pIndicator->SetPosition(_position);

	TextProperties newTextProperties;
	//sf::Vector2f charPreviwPos = _position;
	newTextProperties.OutlineColor = sf::Color::White;
	newTextProperties.iCharacterSize = 36;
	newTextProperties.String = " ";
	newTextProperties.v2fStartPos = { _position.x, _position.y + HEIGHTOFFSET };
	GUI::GetInstance().CreateText(m_sCharPreviewLabel_Next, newTextProperties);

	newTextProperties.v2fStartPos = { _position.x, _position.y - HEIGHTOFFSET };
	GUI::GetInstance().CreateText(m_sCharPreviewLabel_Prev, newTextProperties);

}

InputIndicator::~InputIndicator()
{
	if (m_pIndicator!=nullptr)
	{
		delete m_pIndicator;
		m_pIndicator = nullptr;
	}
}

void InputIndicator::SetPosition(sf::Vector2f _position)
{
	m_pIndicator->SetPosition(_position);

	GUI::GetInstance().GetText(m_sCharPreviewLabel_Next).setPosition({ _position.x, _position.y + HEIGHTOFFSET });
	GUI::GetInstance().GetText(m_sCharPreviewLabel_Prev).setPosition({ _position.x, _position.y - HEIGHTOFFSET });
}

void InputIndicator::SetIndicatorChar(int _charCode)
{
	char prevChar = _charCode - 1;
	char nextChar = _charCode + 1;

	if (prevChar < ' ')
	{
		prevChar = 'z';
	}

	if (nextChar > 'z')
	{
		nextChar = ' ';
	}

	GUI::GetInstance().SetText(m_sCharPreviewLabel_Prev, { prevChar });
	GUI::GetInstance().SetText(m_sCharPreviewLabel_Next, { nextChar });
}

void InputIndicator::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(*m_pIndicator);
}

sf::Vector2f InputIndicator::GetPosition()
{
	return m_pIndicator->GetPosition();
}
