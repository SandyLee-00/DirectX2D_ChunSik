///SoundManager 클래스
///fmod를 사용했다.
// #pragma once
// #include "Singleton.h"
// #include <fmod.h>
// class SoundManager : public Singleton<SoundManager>
// {
// public:
// 	// 사운드 시스템
// 	FMOD_SYSTEM* fsystem;
// 	FMOD_SOUND* sound[32];
// 	FMOD_RESULT result;
// 	FMOD_CHANNEL* channelMusic;
// 	FMOD_CHANNEL* channelEffect;
// 
// 	unsigned int _position;
// 
// 	enum Music {
// 		EXAMPLE,
// 		EXAMPLESound,
// 		END,
// 	};
// 
// 	SoundManager() {};
// 	~SoundManager() {};
// 
// 	void Init() {};
// 	void SoundInit();
// 	void EffectPlay(Music _index);
// 	void MusicPlay(Music _index);
// 	void ReleaseSound();
// 	void EffectStop();
// 	void MusicStop();
// 	unsigned GetAudioPlayBackTime();
// };
// 
