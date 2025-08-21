#pragma once

#include "Framework/Component.h"

class Enemy : public errera::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other);

	void Read(const errera::json::value_t& value) override;
};