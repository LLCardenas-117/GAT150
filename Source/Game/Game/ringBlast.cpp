#include "ringBlast.h"

#include "Engine.h"
#include "Audio/AudioSystem.h"

void ringBlast::Update(float dt) {
    transform.scale += 50.0f * dt;

    Actor::Update(dt);
}

void ringBlast::OnCollision(Actor* other) {

}