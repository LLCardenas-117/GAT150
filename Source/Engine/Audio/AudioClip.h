#pragma once

#include "Resources/Resource.h"

namespace errera {
	class AudioClip : public Resource {
	public:
		AudioClip() = default;

		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;

		FMOD::Sound* _sound{ nullptr };
	};
}