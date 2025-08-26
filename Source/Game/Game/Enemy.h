#pragma once

#include "Framework/Component.h"

class Enemy : public errera::Component, public errera::ICollidable, public errera::IObserver {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

	errera::RigidBody* _rigidBody{ nullptr };

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other) override;

	void OnNotify(const errera::Event& event) override;

	void Read(const errera::json::value_t& value) override;
};