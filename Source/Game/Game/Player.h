#pragma once
#include "Framework/Component.h"

class Player : public errera::Component {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

public:
	Player() = default;
	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other);

	void Read(const errera::json::value_t& value) override;
};