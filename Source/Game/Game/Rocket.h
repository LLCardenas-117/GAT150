#pragma once

#include "Framework/Component.h"

class Rocket : public errera::Component, public errera::ICollidable {
public:
	float speed = 200;

	errera::RigidBody* _rigidBody{ nullptr };

public:
	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void Read(const errera::json::value_t& value) override;
};