//#include "AudioManager.h"
//
//void AudioManager::InitializeAudio()
//{
//	result = FMOD::System_Create(&system);
//	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
//}
//
//void AudioManager::PlaySound1()
//{
//	result = system->playSound(sound1, 0, true, &channel);
//	channel->setVolume(1.0f);
//	channel->setPaused(false);
//}
//
//void AudioManager::PlaySound2()
//{
//	result = system->playSound(sound2, 0, true, &channel);
//	channel->setVolume(1.0f);
//	channel->setPaused(false);
//}
//
//void AudioManager::PlaySoundTrack()
//{
//	result = system->playSound(sound3, 0, true, &channel);
//	channel->setPan(0.0f);
//	channel->setVolume(0.7f);
//	channel->setPaused(false);
//}
//
//void AudioManager::PlaySound4()
//{
//	result = system->playSound(sound4, 0, true, &channel);
//	channel->setVolume(1.0f);
//	channel->setPaused(false);
//}
//
//void AudioManager::PlaySound5()
//{
//	result = system->playSound(sound5, 0, true, &runningchannel);
//	channel->setVolume(1.0f);
//	channel->setPaused(false);
//}
//
//void AudioManager::StopSound5() {
//	if (runningchannel != nullptr) {
//		runningchannel->stop();  // Stop the running sound when the character stops
//	}
//}
//
//void AudioManager::LoadSounds()
//{
//	result = system->createSound("wall_bump.wav", FMOD_DEFAULT, 0, &sound1);
//	result - sound1->setMode(FMOD_LOOP_OFF);
//
//	result = system->createSound("collect.wav", FMOD_DEFAULT, 0, &sound2);
//	result - sound2->setMode(FMOD_LOOP_OFF);
//
//	result = system->createSound("gentle_water.wav", FMOD_DEFAULT, 0, &sound3);
//	result - sound3->setMode(FMOD_LOOP_NORMAL);
//
//	result = system->createSound("jump.wav", FMOD_DEFAULT, 0, &sound4);
//	result - sound4->setMode(FMOD_LOOP_OFF);
//
//	result = system->createSound("running.wav", FMOD_DEFAULT, 0, &sound5);
//	result - sound5->setMode(FMOD_LOOP_OFF);
//}
//
//void AudioManager::UpdateSound()
//{
//	result = system->update();
//}
//
//AudioManager::AudioManager()
//{
//}
//
//AudioManager::~AudioManager() {
//	if (sound1) sound1->release();
//	if (sound2) sound2->release();
//	if (system) system->release();
//}