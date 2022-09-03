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

	if (FindState(_stateName))
	{
		m_sCurrentState = _stateName;
		AnimStateProperties* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
		m_Mesh.setTexture(*currentStateProp->StateTexture);
		m_irectSpriteFrame.left = 0;
		m_iMaxLeftFramePos = (currentStateProp->NumberOfFrames - 1) * currentStateProp->FrameHeight;
		m_Mesh.setTextureRect(m_irectSpriteFrame);
		m_Mesh.setScale(currentStateProp->Scale);
		SetOriginCenter(m_Mesh);
		return true;
	}
	else
	{
		printf("WARN [Animator]: Unable to change state\n");
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
	}

	if (!m_sCurrentState.empty())
	{
		m_bError = false;
		AnimStateProperties* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
		m_fAnimationProgress += Statics::fDeltaTime;
		if (m_fAnimationProgress >= currentStateProp->FrameInterval)
		{
			m_fAnimationProgress = 0.0f;
			int newLeftFrameCoord = m_irectSpriteFrame.left + currentStateProp->FrameHeight;
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
	else if(!m_bError)
	{
		printf("ERR [Animator]: No states to animate\n");
		m_bError = true;
	}
}

void Animator::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
}

bool Animator::FindState(std::string _stateName)
{
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
