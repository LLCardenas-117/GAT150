#include "AudioClip.h"

#include "AudioSystem.h"

namespace errera {
	AudioClip::~AudioClip() {
		if (_sound) _sound->release();
	}

	bool AudioClip::Load(const std::string& filename, AudioSystem& audioSystem) {
		FMOD_RESULT result = audioSystem._system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &_sound);
		if (!AudioSystem::CheckFMODResult(result)) return false;

		return true;
	}

}