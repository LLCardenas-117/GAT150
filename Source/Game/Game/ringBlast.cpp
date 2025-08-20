#include "ringBlast.h"

#include "../GamePCH.h"

FACTORY_REGISTER(ringBlast)

void ringBlast::Update(float dt) {
    owner->transform.scale += 1.25f * dt;
}

void ringBlast::OnCollision(errera::Actor* other) {

}

void ringBlast::Read(const errera::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
}
