#pragma once

#include "Framework/Component.h"

namespace errera {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
}