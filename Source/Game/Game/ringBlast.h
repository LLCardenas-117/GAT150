#pragma once

#include "Framework/Component.h"

class ringBlast : public errera::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

public:
	ringBlast() = default;
	CLASS_PROTOTYPE(ringBlast)

	void Update(float dt) override;

	void OnCollision(class errera::Actor* other);

	void Read(const errera::json::value_t& value) override;
};