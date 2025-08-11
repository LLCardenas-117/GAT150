#include "Font.h"

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
			Logger::Error("Could not load font: {}", name);
			return false;
		}

		return true;
	}
}

