#include "Actor.h"
#include "Renderer/Renderer.h"

#include "Components/RendererComponent.h"

namespace errera {
	FACTORY_REGISTER(Actor)

	Actor::Actor(const Actor& other) :
		Object{other},
		tag{other.tag},
		lifespan{other.lifespan},
		transform{other.transform}
	{
		// Copy components
		for (auto& component : other._components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	void Actor::Update(float dt) {
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		// Update all components
		for (auto& component : _components) {
			if (component->active) component->Update(dt);
		}
	}

	void Actor::Draw(Renderer& renderer) {
		if (destroyed) return;

		for (auto& component : _components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;

		_components.push_back(std::move(component));
	}

	void Actor::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		// Read components
		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}

}

