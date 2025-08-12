#include "Actor.h"
#include "Renderer/Renderer.h"

#include "Components/RendererComponent.h"

namespace errera {
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

}

