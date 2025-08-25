#pragma once

#include "Json.h"

namespace errera {
	class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual void Read(const json::value_t& value) = 0;
	};
}