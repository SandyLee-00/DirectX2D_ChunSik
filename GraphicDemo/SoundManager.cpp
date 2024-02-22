// #include "SoundManager.h"
// #include <windows.h>
// void SoundManager::SoundInit()
// {
// 	// FMOD 시스템 객체 초기화
// 	result = FMOD_System_Create(&fsystem, FMOD_VERSION);
// 	result = FMOD_System_Init(fsystem, 32, FMOD_INIT_NORMAL, NULL);
// 
// 	result = FMOD_System_CreateSound(fsystem, "./Music/Super-Shy.mp3", FMOD_DEFAULT, 0, &sound[EXAMPLE]);
// 	result = FMOD_System_CreateSound(fsystem, "./Music/a.mp3", FMOD_DEFAULT, 0, &sound[EXAMPLESound]); //타이틀
// }
// 
// void SoundManager::EffectPlay(Music _index)
// {
// 	FMOD_System_PlaySound(fsystem, sound[_index], NULL, 0, &channelEffect);
// 	FMOD_Channel_SetMode(channelEffect, FMOD_LOOP_OFF);
// }
// 
// void SoundManager::MusicPlay(Music _index)
// {
// 	FMOD_System_PlaySound(fsystem, sound[_index], NULL, 0, &channelMusic);
// 	FMOD_Channel_SetMode(channelMusic, FMOD_LOOP_NORMAL);
// }
// 
// void SoundManager::ReleaseSound()
// {
// 	for (int i = 0; i < 32; i++) {
// 		FMOD_Sound_Release(sound[i]);
// 	}
// 	FMOD_System_Close(fsystem);
// 	FMOD_System_Release(fsystem);
// }
// 
// void SoundManager::EffectStop()
// {
// 	FMOD_Channel_Stop(channelEffect);
// }
// 
// void SoundManager::MusicStop()
// {
// 	FMOD_Channel_Stop(channelMusic);
// }
// 
// unsigned SoundManager::GetAudioPlayBackTime()
// {
// 	_position = 0;
// 	result = FMOD_Channel_GetPosition(channelMusic, &_position, FMOD_TIMEUNIT_MS);
// 	return 0;
// }
