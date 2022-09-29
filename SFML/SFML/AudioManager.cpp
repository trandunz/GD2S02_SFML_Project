// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: AudioManager.cpp 
// Description  : AudioManager Implementation File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#include "AudioManager.h"

void AudioManager::PlayMusic(std::string _song, bool _loop)
{
	m_Jutebox.setLoop(_loop);
	m_Jutebox.openFromFile("Resources/Sounds/Songs/" + _song);
	m_Jutebox.play();
}

void AudioManager::PauseMusic()
{
	m_Jutebox.pause();
}

void AudioManager::StopMusic()
{
	m_Jutebox.stop();
}

void AudioManager::CreateAudioSource(std::string _key)
{
	m_AudioSources.insert_or_assign(_key, new sf::Sound());
}

void AudioManager::CreateAudioSource(std::string _key, std::string _sound)
{
	m_AudioSources.insert_or_assign(_key, new sf::Sound());
	m_AudioSources[_key]->setBuffer(LoadSound(_sound));
}

void AudioManager::PlayAudioSource(std::string _key)
{
	if (m_AudioSources[_key] != nullptr)
	{
		m_AudioSources[_key]->play();
	}
}

sf::SoundBuffer& AudioManager::LoadSound(std::string _sound)
{
	if (m_LoadedSounds[_sound] == nullptr)
	{
		m_LoadedSounds.insert_or_assign(_sound, new sf::SoundBuffer());

		// Load the sound
		m_LoadedSounds[_sound]->loadFromFile("Resources/Sounds/" + _sound);
	}
	return *m_LoadedSounds[_sound];
}

void AudioManager::SetSound(std::string _audioSource, std::string _sound)
{
	if (m_AudioSources[_audioSource] != nullptr)
	{
		m_AudioSources[_audioSource]->setBuffer(LoadSound(_sound));
	}
}

void AudioManager::Cleanup()
{
	// Cleanup all audio sources
	for (auto& audioSource : m_AudioSources)
	{
		if (audioSource.second != nullptr)
		{
			delete audioSource.second;
			audioSource.second = nullptr;
		}
	}
	// Cleanup all loaded sounds
	for (auto& buffer : m_LoadedSounds)
	{
		if (buffer.second != nullptr)
		{
			delete buffer.second;
			buffer.second = nullptr;
		}
	}
	m_AudioSources.clear();
	m_LoadedSounds.clear();
}
