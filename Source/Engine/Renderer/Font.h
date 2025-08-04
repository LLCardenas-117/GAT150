#pragma once 

#include <string>

struct TTF_Font;

namespace errera {
	class Font {
	public:
		Font() = default;

		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* _ttfFont{ nullptr };
	};
}