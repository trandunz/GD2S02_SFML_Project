// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Animator.cpp 
// 
// Description :
//  General purpose file to store and animate spritesheets.
//	Stores different animations tied to string name and records
//  a state as default. Will not run without at least one state added.
//	Animations can be set to loop, otherwise it will change back to
//  Default state after displaying the last frame			
// Author : Chuang, Kee

#include "Animator.h"
#include "Math.h"
#include "TextureLoader.h"

Animator::Animator()
{
	int imgHeight = (int)IMG_HEIGHT;
	m_irectSpriteFrame = { 0,0,imgHeight,imgHeight };
	m_fAnimationProgress = 0.0f;
	m_iMaxLeftFramePos = IMG_HEIGHT;
}

Animator::~Animator()
{
	CleanupMap(m_mapAnimationStates);
}

void Animator::AddState(std::string _stateName, AnimStateProperties _properties)
{
	m_mapAnimationStates.insert_or_assign(_stateName, _properties);
}

bool Animator::SetDefaultState(std::string _stateName)
{
	if (FindState(_stateName))
	{
		m_sDefaultState = _stateName;
		return true;
	}
	else
	{
		printf("WARN [Animator]: Unable to set default state\n");
		return false;
	}
}

bool Animator::StartState(std::string _stateName)
{
	//Find the state with the given name, then set the current state to that name
	//and set the sprite properties to that ones corresponding to that state with that name
	if (FindState(_stateName))
	{
		m_sCurrentState = _stateName;
		AnimStateProperties* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
		m_Mesh.setTexture(*currentStateProp->StateTexture);
		m_irectSpriteFrame.left = 0;
		//max left frame refers to the maximuim value of the top left coordinate of the frame 
		//is calculated by mutltiplying the frame width
		//with the number of frames (minus one because the first frame is of coordinate zero)
		m_iMaxLeftFramePos = (currentStateProp->NumberOfFrames - 1) * currentStateProp->FrameWidth;
		m_Mesh.setTextureRect(m_irectSpriteFrame);
		m_Mesh.setScale(currentStateProp->Scale);
		SetOriginCenter(m_Mesh);

		currentStateProp = nullptr;
		return true;
	}
	else
	{
		Print("WARN [Animator]: Unable to change state");
		return false;
	}
}

void Animator::Update()
{ 
	if (m_sCurrentState.empty())
	{
		if (!m_sDefaultState.empty())
		{
			m_sCurrentState = m_sDefaultState;
		}
		else
		{
			Print("WARN [Animator]: No default state recorded");
		}
	}

	if (!m_sCurrentState.empty())
	{
		m_bError = false;
		//Get a pointer to the current state properties before addind to
		//the current animation progress. We need to know how long this frame lasts
		AnimStateProperties* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
		m_fAnimationProgress += Statics::fDeltaTime;
		if (m_fAnimationProgress >= currentStateProp->FrameInterval)
		{
			m_fAnimationProgress = 0.0f;
			//If the current progress is equal or longer than the interval, then change to the next frame.
			//We do this by changing the texture rect value of the sprite. We add 32 (or whatever the image width is)
			//to the top left coordinate to change which part of the spritesheet to use.
			//We also check that teh coordinate is not outside the actual image before we update the sprite.
			//If it is, we either 
			// a: reset the coordinate to 0 if we're looping
			// b: start the default animation.
			int newLeftFrameCoord = m_irectSpriteFrame.left + currentStateProp->FrameWidth;
			if (newLeftFrameCoord > m_iMaxLeftFramePos)
			{
				m_irectSpriteFrame.left = 0;
				m_Mesh.setTextureRect(m_irectSpriteFrame);

				if (!currentStateProp->Loops)
				{
					StartState(m_sDefaultState);
				}
			}
			else
			{
				m_irectSpriteFrame.left = newLeftFrameCoord;
				m_Mesh.setTextureRect(m_irectSpriteFrame);
			}
		}
	}
	//If the currentState is still empty (i.e. doesn't contain a name, then the animator
	//is in an errorneous state. If this is the first time we've reached this part of the loop,
	//then print an error and set m_bError to true so that we don't print it again.
	else if(!m_bError)
	{
		Print("ERR [Animator]: No states to animate");
		m_bError = true;
	}
}

void Animator::SetScale(const sf::Vector2f& _factors)
{
	m_Mesh.setScale(_factors);
}

void Animator::SetScale(float _factorX, float _factorY)
{
	m_Mesh.setScale(_factorX, _factorY);
}

void Animator::SetPosition(const sf::Vector2f& _position)
{
	m_Mesh.setPosition(_position);
}

void Animator::SetPosition(float _positionX, float _positionY)
{
	m_Mesh.setPosition(_positionX, _positionY);
}

void Animator::MoveSprite(const sf::Vector2f& _offset)
{
	m_Mesh.move(_offset);
}

void Animator::MoveSprite(float _offsetX, float _offsetY)
{
	m_Mesh.move(_offsetX, _offsetY);
}

void Animator::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
}

bool Animator::FindState(std::string _stateName)
{
	//find a the key with the same name and return it if it exists
	if (m_mapAnimationStates.find(_stateName) != m_mapAnimationStates.end())
	{
		return true;
	}
	else
	{
		printf("ERROR [Animator]: no such state exists( %s )\n", _stateName.c_str());
		return false;
	}
}
