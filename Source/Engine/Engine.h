#pragma once
#include "Core/Time.h"

#include <memory>

namespace errera {
	class AudioSystem;
	class InputSystem;
	class Renderer;
	class ParticleSystem;

	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Update();
		void Draw();
		void Shutdown();

		Renderer& GetRenderer() { return *_renderer; }
		InputSystem& GetInput() { return *_input; }
		AudioSystem& GetAudio() { return *_audio; }
		ParticleSystem& GetParticleSystem() { return *_particleSystem; }

		Time& GetTime() { return _time; }

	private:
		Time _time;

		std::unique_ptr<AudioSystem> _audio;
		std::unique_ptr<InputSystem> _input;
		std::unique_ptr<Renderer> _renderer;
		std::unique_ptr<ParticleSystem> _particleSystem;
	};

	Engine& GetEngine();
}