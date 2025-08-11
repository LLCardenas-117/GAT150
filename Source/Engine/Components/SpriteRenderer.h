#pragma once

#include "RendererComponent.h"

namespace errera {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;
	};
}