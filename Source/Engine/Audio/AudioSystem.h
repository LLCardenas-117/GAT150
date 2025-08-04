#pragma once

#include <fmod.hpp>
#include <string>
#include <map>

namespace errera {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();

		void Shutdown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "");
		bool PlaySound(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);

	private:
		FMOD::System* _system{ nullptr };
		std::map<std::string, FMOD::Sound*> _sounds;

	};
}