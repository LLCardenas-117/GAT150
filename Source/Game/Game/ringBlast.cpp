#include "ringBlast.h"

FACTORY_REGISTER(ringBlast)

void ringBlast::Update(float dt) {
    transform.scale += 1.25f * dt;

    Actor::Update(dt);
}

void ringBlast::OnCollision(Actor* other) {

}