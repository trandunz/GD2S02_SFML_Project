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

float AudioManager::m_MusicVolume = 50.0f;
float AudioManager::m_EffectsVolume = 50.0f;
bool AudioManager::m_MusicMuted = false;
bool AudioManager::m_EffectsMuted = false;

void AudioManager::PlayMusic(std::string _song, bool _loop)
{
	m_Jutebox.setLoop(_loop);
	m_Jutebox.openFromFile("Resources/Sounds/Songs/" + _song);
	m_Jutebox.setVolume(m_MusicVolume);

	if (m_MusicMuted)
		MuteMusic();

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

void AudioManager::SetMusicVolume(float _volume)
{
	m_Jutebox.setVolume(_volume);
	m_MusicVolume = _volume;
	m_MusicMuted = false;
}

void AudioManager::IncrementMusicVolume(float _amount)
{
	m_MusicVolume += _amount;
	if (m_MusicVolume > 100)
		m_MusicVolume = 100.0f;

	m_Jutebox.setVolume(m_MusicVolume);
	m_MusicMuted = false;
}

void AudioManager::DecrementMusicVolume(float _amount)
{
	m_MusicVolume -= _amount;
	if (m_MusicVolume < 0)
		m_MusicVolume = 0.0f;

	m_Jutebox.setVolume(m_MusicVolume);
	m_MusicMuted = false;
}

void AudioManager::MuteMusic()
{
	m_Jutebox.setVolume(0);
	m_MusicMuted = true;
}

void AudioManager::ToggleMuteMusic()
{
	m_MusicMuted = !m_MusicMuted;
	if (m_MusicMuted == false)
	{
		m_Jutebox.setVolume(m_MusicVolume);
	}
	else
	{
		m_Jutebox.setVolume(0);
	}	
}

void AudioManager::SetEffectsVolume(float _volume)
{
	m_EffectsVolume = _volume;
	m_EffectsMuted = false;
	for (auto& audioSource : m_AudioSources)
	{
		audioSource.second->setVolume(_volume);
	}
}

void AudioManager::IncrementEffectsVolume(float _amount)
{
	m_EffectsVolume += _amount;
	if (m_EffectsVolume > 100)
		m_EffectsVolume = 100.0f;

	for (auto& audioSource : m_AudioSources)
	{
		audioSource.second->setVolume(m_EffectsVolume);
	}
	m_EffectsMuted = false;
}

void AudioManager::DecrementEffectsVolume(float _amount)
{
	m_EffectsVolume -= _amount;
	if (m_EffectsVolume < 0)
		m_EffectsVolume = 0.0f;

	for (auto& audioSource : m_AudioSources)
	{
		audioSource.second->setVolume(m_EffectsVolume);
	}
	m_EffectsMuted = false;
}

void AudioManager::MuteEffects()
{
	for (auto& audioSource : m_AudioSources)
	{
		audioSource.second->setVolume(0);
	}
	m_EffectsMuted = true;
}

void AudioManager::ToggleMuteEffects()
{
	m_EffectsMuted = !m_EffectsMuted;
	for (auto& audioSource : m_AudioSources)
	{
		if (m_EffectsMuted == false)
		{
			audioSource.second->setVolume(m_EffectsVolume);
		}
		else
		{
			audioSource.second->setVolume(0);
		}
	}
}

bool AudioManager::IsMusicMuted()
{
	return m_MusicMuted;
}

bool AudioManager::IsEffectsMuted()
{
	return m_EffectsMuted;
}

float AudioManager::GetMusicVolume()
{
	return m_MusicVolume;
}

float AudioManager::GetEffectsVolume()
{
	return m_EffectsVolume;
}

void AudioManager::CreateAudioSource(std::string _key)
{
	m_AudioSources.insert_or_assign(_key, new sf::Sound());
	m_AudioSources[_key]->setVolume(m_EffectsVolume);
	if (m_EffectsMuted)
		MuteEffects();
}

void AudioManager::CreateAudioSource(std::string _key, std::string _sound)
{
	m_AudioSources.insert_or_assign(_key, new sf::Sound());
	m_AudioSources[_key]->setBuffer(LoadSound(_sound));
	m_AudioSources[_key]->setVolume(m_EffectsVolume);
	if (m_EffectsMuted)
		MuteEffects();
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
		m_AudioSources[_audioSource]->setVolume(m_MusicVolume);
	}
}

sf::SoundSource::Status AudioManager::GetAudioSourceStatus(std::string _audioSource)
{
	if (m_AudioSources[_audioSource] != nullptr)
	{
		return m_AudioSources[_audioSource]->getStatus();
	}
	return sf::SoundSource::Status();
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
