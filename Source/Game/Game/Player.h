#pragma once
#include "Framework/Actor.h"

class Player : public errera::Actor {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

public:
	Player() = default;
	Player(const errera::Transform& transform) :
		Actor{ transform }
	{}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

};