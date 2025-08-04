#pragma once

#include "Framework/Actor.h"

class Rocket : public errera::Actor {
public:
	float speed = 200;

public:
	Rocket() = default;
	Rocket(const errera::Transform& transform, std::shared_ptr<errera::Model> model) :
		Actor{ transform, model }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};