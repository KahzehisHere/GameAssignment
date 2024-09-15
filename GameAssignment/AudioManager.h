#pragma once
#include "fmod.hpp"
class AudioManager
{
public:
	FMOD::System* system; //pointer to Virtual Sound Card
	FMOD::Sound* sound1, * sound2, * sound3, * sound4, * sound5, * stopsound5; //sound files
	FMOD::Channel* channel, * runningchannel; //Sound files are played and mixed
	FMOD_RESULT result;
	void* extradriverdata = 0;

	void InitializeAudio(); //Initializing FMOD sound card
	void PlaySound1(); // play sound 1
	void PlaySound2();
	void PlaySound4();
	void PlaySound5();
	void StopSound5();
	void PlaySoundTrack();
	void LoadSounds(); // read sound file from Hdd, load to sound card
	void UpdateSound(); // update any sound parameters - call EVERY loop

	AudioManager();
	~AudioManager();
};