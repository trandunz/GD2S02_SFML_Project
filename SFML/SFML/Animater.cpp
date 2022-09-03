// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Animater.cpp 
// 
// Description :
//  General purpose file to store and animate spritesheets.
//	Stores different animations tied to string name and records
//  a state as default. Will not run without at least one state added.
//	Animations can be set to loop, otherwise it will change back to
//  Default state after displaying the last frame			
// Author : Chuang, Kee

#include "Animater.h"
#include "Statics.h"
#include "Math.h"

Animater::Animater()
{
	int imgHeight = (int)IMG_HEIGHT;
	m_irectSpriteFrame = { 0,0,imgHeight,imgHeight };
	m_fAnimationProgress = 0.0f;
	m_iMaxLeftFramePos = IMG_HEIGHT;
}

Animater::~Animater()
{
	for (auto& mapElement : m_mapAnimationStates)
	{
		if (mapElement.second.StateTexture != nullptr)
		{
			mapElement.second.StateTexture = nullptr;
		}
	}

	m_mapAnimationStates.clear();
}

void Animater::AddState(std::string _stateName, AnimStateProp _properties)
{
	m_mapAnimationStates.insert_or_assign(_stateName, _properties);
}

bool Animater::SetDefaultState(std::string _stateName)
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

bool Animater::StartState(std::string _stateName)
{

	if (FindState(_stateName))
	{
		m_sCurrentState = _stateName;
		AnimStateProp* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
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

void Animater::Update()
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
		AnimStateProp* currentStateProp = &m_mapAnimationStates[m_sCurrentState];
		m_fAnimationProgress += Statics::DeltaTime;
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

void Animater::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Mesh);
}

bool Animater::FindState(std::string _stateName)
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
