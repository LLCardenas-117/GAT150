#include "Actor.h"
#include "../Renderer/Model.h"

namespace errera {
	void Actor::Update(float dt) {
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer) {
		if (destroyed) return;

		_model->Draw(renderer, transform);
	}

	float Actor::GetRadius() {
		return (_model) ? _model->GetRadius() * transform.scale * 0.8f : 0;
	}

}

