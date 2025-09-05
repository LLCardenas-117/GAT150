#pragma once

#include "Framework/Component.h"

class Player2Controller : public errera::Component, public errera::ICollidable {
public:
	float speed = 0;
	float maxSpeed = 0;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
	int health = 3;
	bool healthUpdate = false;
	bool actionOver;

	errera::RigidBody* _rigidBody{ nullptr };

public:
	Player2Controller() = default;
	CLASS_PROTOTYPE(Player2Controller)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void Read(const errera::json::value_t& value) override;
};