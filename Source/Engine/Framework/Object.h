#pragma once
#include <string>

namespace errera {
	class Object {
	public:
		std::string name;
		bool active{ true };

	public:
		Object() = default;
		virtual ~Object() = default;
	};
}