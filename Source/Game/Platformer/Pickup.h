#pragma once

#include "Framework/Component.h"

class Pickup : public errera::Component, public errera::ICollidable {
public:
	errera::RigidBody* _rigidBody{ nullptr };

public:
	Pickup() = default;
	CLASS_PROTOTYPE(Pickup)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void Read(const errera::json::value_t& value) override;
};