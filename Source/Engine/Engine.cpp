#include "Engine.h"

namespace errera {
	bool Engine::Initialize() {
		_renderer = std::make_unique<Renderer>();
		_renderer->Initialize();
		_renderer->CreateWindow("ERRERA Engine", 1280, 1024);

		_input = std::make_unique<InputSystem>();
		_input->Initialize();

		_audio = std::make_unique<AudioSystem>();
		_audio->Initialize();

		_particleSystem = std::make_unique<ParticleSystem>();
		_particleSystem->Initialize(5000);
		return true;
	}

	void Engine::Update() {
		_time.Tick();
		_input->Update();
		_audio->Update();
		_particleSystem->Update(_time.GetDeltaTime());
	}

	void Engine::Draw() {
		//
	}

	void Engine::Shutdown()	{
		_particleSystem->ShutDown();
		_audio->Shutdown();
		_input->Shutdown();
		_renderer->Shutdown();
	}
}

