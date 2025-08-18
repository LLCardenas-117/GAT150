#pragma once

#include "Framework/Component.h"

class Enemy : public errera::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	Enemy() = default;
	/*Enemy(const errera::Transform& transform) :
		Actor{ transform }
	{
	}*/

	void Update(float dt) override;

	void OnCollision(class Actor* other);
};