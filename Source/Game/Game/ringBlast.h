#pragma once

#include "Framework/Component.h"

class ringBlast : public errera::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	ringBlast() = default;
	/*ringBlast(const errera::Transform& transform) :
		Actor{ transform }
	{
	}*/

	void Update(float dt) override;

	void OnCollision(class Actor* other);
};