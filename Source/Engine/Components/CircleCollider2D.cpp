#include "EnginePCH.h"
#include "CircleCollider2D.h"

namespace errera {
	FACTORY_REGISTER(CircleCollider2D)

	void errera::CircleCollider2D::Update(float dt) {
		//
	}

	bool errera::CircleCollider2D::CheckCollision(ColliderComponent& other) {

		float distance = (owner->transform.position - other.owner->transform.position).Length();

		// Check circle to circle collision
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);

		if (circleCollider) {
			float radii = radius + circleCollider->radius;
			if (distance <= radii) return true;
		}

		return false;
	}
	void CircleCollider2D::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, radius);
	}
}

