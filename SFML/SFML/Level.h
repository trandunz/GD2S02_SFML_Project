// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Level.h 
// Description : Level Header File
// Author : Inman, Will

#pragma once

class Level
{
public:
	Level() {}
	virtual ~Level() {}

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	float m_fElaspedTime{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	float GetElaspedTime();
};