///SoundManager Å¬·¡½º
///fmod¸¦ »ç¿ëÇß´Ù.
#pragma once
#include "Singleton.h"
#include <fmod.hpp>
#include <string>

class ManagerSet;
class PathManager;
class SoundManager : public Singleton<SoundManager>
{
	PathManager* pm;
public:
	// »ç¿îµå ½Ã½ºÅÛ
	FMOD::System* fsystem;
	FMOD::Sound* sound[32];
	FMOD_RESULT result;
// 	FMOD::Channel* channelMusic;
// 	FMOD::Channel* channelEffect;
// 	FMOD::Channel* channelVoice;
	FMOD::Channel* channels[32];
	float musicVolume;
	float effectVolume;

	unsigned int _position;

	enum Music {
		Opening,
		Main,
		Ranking,
		Title,
		BUTTON,
		PLAYERMOVE,
		SUPATTACK,
		SUPHIT,
		SUPSHIED,
		SHILDING,
		FROZENMON,
		DEADMON,
		DEALATTACK, //µô·¯ ÄÆ¾À
		DEALSKILLATCK, //µô·¯½ºÅ³ÀÌÆåÆ®
		DEALVOICE, //µô·¯ º¸ÀÌ½º
		DEALHIT,
		GUNHIT,
		GuNATTACK,
		GUNATTRACKSUCS,
		SoundScore,
		SOUNDGAMEOVER,
		SOUNDCLEAR,
		SOUNDRANKIN,
		SOUNDTYPING,
		END,
	};

	enum Channels
	{
		BGM,
		PLAYEREFFECT,
		MONSTEREFFECT,
		DEALEREFFECT,
		SCENEEFFECT,
		MOUSEEFFECT,
		GUARDIANEFFECT,
		VOICE,
	};

	SoundManager();
	~SoundManager();

	void Init() {};
	void SoundInit(PathManager* _pm);
// 	void EffectPlay(Music _index);
// 	void MusicPlay(Music _index);
// 	void VoicePlay(Music _index);
	void ReleaseSound();
// 	void EffectStop();
// 	void MusicStop();
// 	void VoiceStop();

	void Play(Channels _channel, Music _music, bool _loop = false);
	void Stop(Channels _channel);
	void Update();

	unsigned GetAudioPlayBackTime(Channels _channel);
	std::string GetPathSound(std::wstring path);
};

