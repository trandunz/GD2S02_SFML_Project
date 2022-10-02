// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// 
// File Name	: AudioManager.h 
// Description  : AudioManager Header File
// Author		: William Inman
// Email		: william.inman@mds.ac.nz

#pragma once
#include <SFML/Audio.hpp>
#include <map>

class AudioManager
{
public:
	/// <summary>
	/// Play the song at the specified file path
	/// </summary>
	/// <param name="_song"></param>
	/// <param name="_loop"></param>
	static void PlayMusic(std::string _song, bool _loop = true);
	/// <summary>
	/// Pause the current song
	/// </summary>
	static void PauseMusic();
	/// <summary>
	/// Stop the current song
	/// </summary>
	static void StopMusic();
	static void SetMusicVolume(float _volume);
	static void IncrementMusicVolume(float _amount);
	static void DecrementMusicVolume(float _amount);
	static void MuteMusic();
	static void ToggleMuteMusic();
	static void SetEffectsVolume(float _volume);
	static void IncrementEffectsVolume(float _amount);
	static void DecrementEffectsVolume(float _amount);
	static void MuteEffects();
	static void ToggleMuteEffects();
	static bool IsMusicMuted();
	static bool IsEffectsMuted();
	static float GetMusicVolume();
	static float GetEffectsVolume();
	/// <summary>
	/// Create an audio source with the given key
	/// </summary>
	/// <param name="_key"></param>
	static void CreateAudioSource(std::string _key);
	/// <summary>
	/// Create an audio source with the given key and sound
	/// </summary>
	/// <param name="_key"></param>
	/// <param name="_sound"></param>
	static void CreateAudioSource(std::string _key, std::string _sound);
	/// <summary>
	/// Play the specified audio source
	/// </summary>
	/// <param name="_key"></param>
	static void PlayAudioSource(std::string _key);
	/// <summary>
	/// Load the audio clip at the specified file path
	/// </summary>
	/// <param name="_sound"></param>
	/// <returns></returns>
	static sf::SoundBuffer& LoadSound(std::string _sound);
	/// <summary>
	/// Set the audio clip of the specified audio source 
	/// </summary>
	/// <param name="_audioSource"></param>
	/// <param name="_sound"></param>
	static void SetSound(std::string _audioSource, std::string _sound);

	/// <summary>
	/// Cleanup all audio sources and loaded audio clips
	/// </summary>
	static void Cleanup();
private:
	static float m_MusicVolume;
	static bool m_MusicMuted;
	static float m_EffectsVolume;
	static bool m_EffectsMuted;
	inline static sf::Music m_Jutebox;
	inline static std::map<std::string, sf::Sound*> m_AudioSources;
	inline static std::map<std::string, sf::SoundBuffer*> m_LoadedSounds;
};

