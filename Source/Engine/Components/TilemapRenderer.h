#pragma once
#include "RendererComponent.h"

namespace errera {
	class TilemapRenderer : public RendererComponent {
	public:
		TilemapRenderer() = default;
		TilemapRenderer(const TilemapRenderer& other);

		CLASS_PROTOTYPE(TilemapRenderer)

		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;

	private:
		std::string _tilemapName;
		res_t<class Tilemap> _tilemap;

		std::vector<std::unique_ptr<PhysicsBody>> _physicsBodies;
	};
}
