#pragma once

#include "Framework/Actor.h"

class Rocket : public errera::Actor {
public:
	float speed = 200;

public:
	Rocket() = default;
	Rocket(const errera::Transform& transform) :
		Actor{ transform }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};