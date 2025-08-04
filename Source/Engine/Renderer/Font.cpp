#include "Font.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>

namespace errera {
	/// <summary>
	/// 
	/// </summary>
	Font::~Font() {
		if (_ttfFont != nullptr) {
			TTF_CloseFont(_ttfFont);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="fontSize"></param>
	/// <returns></returns>
	bool Font::Load(const std::string& name, float fontSize) {
		_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (_ttfFont == nullptr) {
			std::cerr << "Could not load font: " << name << std::endl;
			return false;
		}

		return true;
	}
}

