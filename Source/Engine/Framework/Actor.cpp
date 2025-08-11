#include "Actor.h"
#include "Renderer/Renderer.h"

#include "Components/RendererComponent.h"

namespace errera {
	void Actor::Update(float dt) {
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		for (auto& component : _components) {
			if (component->active) component->Update(dt);
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
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

		//renderer.DrawTexture(_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	float Actor::GetRadius() {
		return 50.0f;
		//return (_texture) ? (_texture->GetSize().Length() * 0.5f) * transform.scale * 0.8f : 0;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;

		_components.push_back(std::move(component));
	}

}

