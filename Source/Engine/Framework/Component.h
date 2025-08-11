#pragma once

#include "Object.h"

namespace errera {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr };

	public:
		Component() = default;

		virtual void Update(float dt) = 0;
	};
}