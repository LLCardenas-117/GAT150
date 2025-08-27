#pragma once
#include "Framework/Component.h"

class Player : public errera::Component, public errera::ICollidable {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	errera::RigidBody* _rigidBody{ nullptr };

public:
	Player() = default;
	CLASS_PROTOTYPE(Player)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void Read(const errera::json::value_t& value) override;
};