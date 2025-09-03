#pragma once

#include "Framework/Component.h"

class FlyingEnemyController : public errera::Component, public errera::ICollidable {
public:
	float speed = 0;
	float maxSpeed = 0;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	errera::RigidBody* _rigidBody{ nullptr };

public:
	FlyingEnemyController() = default;
	CLASS_PROTOTYPE(FlyingEnemyController)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void Read(const errera::json::value_t& value) override;
};