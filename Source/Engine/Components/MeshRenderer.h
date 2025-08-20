#pragma once

#include "RendererComponent.h"

namespace errera {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;

	public:
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}