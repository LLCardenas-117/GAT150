#pragma once

namespace errera {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void OnCollision(class Actor* other) = 0;
	};
}