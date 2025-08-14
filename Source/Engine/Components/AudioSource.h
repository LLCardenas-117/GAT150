#pragma once

#include "Framework/Component.h"

namespace errera {
	class AudioSource : public Component {
	public:
		std::string audioClipName;

	public:
		void Update(float dt) override;
		void Play();
	};
}