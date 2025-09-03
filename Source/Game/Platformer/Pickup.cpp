#include "../GamePCH.h"
#include "Pickup.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	_rigidBody = owner->GetComponent<errera::RigidBody>();
}

void Pickup::Update(float dt) {
	//
}

void Pickup::OnCollision(class errera::Actor* other) {
	if (errera::equalsIqnoreCase(other->tag, "player")) {
		owner->destroyed = true;
	}
}

void Pickup::Read(const errera::json::value_t& value) {
	Object::Read(value);
}