#include "SoundManager.h"
#include <windows.h>
#include "ManagerSet.h"

SoundManager::SoundManager()
	:_position{}
	, sound{}
	, result{}
	, fsystem{}
	, musicVolume(1.0f)
	, effectVolume(1.0f)
	, pm(nullptr)
	, channels{}
{
}

SoundManager::~SoundManager()
{
	ReleaseSound();
}
void SoundManager::SoundInit(PathManager* _pm)
{
	// FMOD 시스템 객체 초기화
	this->pm = _pm;
	result = FMOD::System_Create(&fsystem, FMOD_VERSION);
	result = fsystem->init(32, FMOD_INIT_NORMAL, NULL);

	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\BGM\\Sound_title_BGM.wav").c_str(), FMOD_DEFAULT, 0, &sound[Title]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\BGM\\Sound_main_BGM.wav").c_str(), FMOD_DEFAULT, 0, &sound[Main]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\BGM\\Sound_rank_BGM.wav").c_str(), FMOD_DEFAULT, 0, &sound[Ranking]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\BGM\\Sound_op_BGM.wav").c_str(), FMOD_DEFAULT, 0, &sound[Opening]);

	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_bt.wav").c_str(), FMOD_DEFAULT, 0, &sound[BUTTON]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_sup_move.wav").c_str(), FMOD_DEFAULT, 0, &sound[PLAYERMOVE]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_sup_atk.wav").c_str(), FMOD_DEFAULT, 0, &sound[SUPATTACK]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_sup_hit.wav").c_str(), FMOD_DEFAULT, 0, &sound[SUPHIT]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_sup_sld_use.wav").c_str(), FMOD_DEFAULT, 0, &sound[SUPSHIED]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_sld_eft.wav").c_str(), FMOD_DEFAULT, 0, &sound[SHILDING]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_mon_hold.wav").c_str(), FMOD_DEFAULT, 0, &sound[FROZENMON]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_mon_death.wav").c_str(), FMOD_DEFAULT, 0, &sound[DEADMON]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_ skill_cutscene.wav").c_str(), FMOD_DEFAULT, 0, &sound[DEALATTACK]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_ deal_eft.wav").c_str(), FMOD_DEFAULT, 0, &sound[DEALSKILLATCK]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_ deal_atk.wav").c_str(), FMOD_DEFAULT, 0, &sound[DEALVOICE]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_deal_hit.wav").c_str(), FMOD_DEFAULT, 0, &sound[DEALHIT]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound _Gdn_hit.wav").c_str(), FMOD_DEFAULT, 0, &sound[GUNHIT]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound _Gdn_atk.wav").c_str(), FMOD_DEFAULT, 0, &sound[GuNATTACK]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound _Gdn_atk_eft.wav").c_str(), FMOD_DEFAULT, 0, &sound[GUNATTRACKSUCS]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_score_eft.mp3").c_str(), FMOD_DEFAULT, 0, &sound[SoundScore]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_game_over.wav").c_str(), FMOD_DEFAULT, 0, &sound[SOUNDGAMEOVER]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_clear.wav").c_str(), FMOD_DEFAULT, 0, &sound[SOUNDCLEAR]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_rank_in.wav").c_str(), FMOD_DEFAULT, 0, &sound[SOUNDRANKIN]);
	result = fsystem->createSound(GetPathSound(L"Sound\\sound_wav\\effect\\Sound_rank_typ.wav").c_str(), FMOD_DEFAULT, 0, &sound[SOUNDTYPING]);

	for (int i = 0; i < 32; i++)
	{
		this->channels[i]->setVolume(effectVolume);
	}

}

// void SoundManager::EffectPlay(Music _index)
// {
// 	fsystem->playSound(sound[_index], NULL, 0, &channelEffect);
// 	channelEffect->setMode(FMOD_LOOP_OFF);
// }
// 
// void SoundManager::MusicPlay(Music _index)
// {
// 	fsystem->playSound(sound[_index], NULL, 0, &channelMusic);
// 	channelMusic->setMode(FMOD_LOOP_NORMAL);
// }
// 
// void SoundManager::VoicePlay(Music _index)
// {
// 	fsystem->playSound(sound[_index], NULL, 0, &channelVoice);
// 	channelVoice->setMode(FMOD_LOOP_OFF);
// }

void SoundManager::ReleaseSound()
{
	for (int i = 0; i < 32; i++)
	{
		sound[i]->release();
	}
	fsystem->close();
	fsystem->release();
}

// void SoundManager::EffectStop()
// {
// 	channelEffect->stop();
// }
// 
// void SoundManager::MusicStop()
// {
// 	channelMusic->stop();
// }
// 
// void SoundManager::VoiceStop()
// {
// 	channelVoice->stop();
// }

void SoundManager::Play(Channels _channel, Music _music, bool _loop)
{
	fsystem->playSound(sound[_music], NULL, 0, &this->channels[_channel]);
	if (_loop) 
	{
		this->channels[_channel]->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		this->channels[_channel]->setMode(FMOD_LOOP_OFF);
	}
}

void SoundManager::Stop(Channels _channel)
{
	this->channels[_channel]->stop();
}

void SoundManager::Update()
{
	fsystem->update();
}

unsigned SoundManager::GetAudioPlayBackTime(Channels _channel)
{
	_position = 0;
	result = this->channels[(int)_channel]->getPosition(&_position, FMOD_TIMEUNIT_MS);
	return 0;
}

std::string SoundManager::GetPathSound(std::wstring path)
{
	std::wstring wstr = pm->GetResourcePath(path);
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str(bufferSize, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);

	const char* totalSoundPath = str.c_str();

	return str;
}
