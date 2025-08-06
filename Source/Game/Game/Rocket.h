#pragma once

#include "Framework/Actor.h"

class Rocket : public errera::Actor {
public:
	float speed = 200;

public:
	Rocket() = default;
	Rocket(const errera::Transform& transform, errera::res_t<errera::Texture> texture) :
		Actor{ transform, texture }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};