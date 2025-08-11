#pragma once
#include "Component.h"
#include "Math/Transform.h"
#include "Object.h"
#include "Renderer/Texture.h"

#include <memory>
#include <string>

namespace errera {
	class Actor : public Object {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{transform}
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		// Components
		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> _components;
		//res_t<Texture> _texture;
	};
}