#pragma once

#include "Framework/Component.h"

namespace errera {
	class RendererComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}