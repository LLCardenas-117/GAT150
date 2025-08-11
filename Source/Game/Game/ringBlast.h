#pragma once

#include "Framework/Actor.h"

class ringBlast : public errera::Actor {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	ringBlast() = default;
	ringBlast(const errera::Transform& transform) :
		Actor{ transform }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};