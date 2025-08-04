#include "Texture.h"
#include "Renderer.h"
#include <SDL3_image/SDL_image.h>

#include <iostream>

namespace errera {
	Texture::~Texture() {
		if (!_texture) SDL_DestroyTexture(_texture);
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer) {
		SDL_Surface* surface = IMG_Load(filename.c_str());

		if (!surface) {
			std::cerr << "Could not load image: " << filename << std::endl;
			return false;
		}

		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);

		SDL_DestroySurface(surface);

		if (!_texture) {
			std::cerr << "Could not create texture: " << filename << std::endl;
			return false;
		}

		return true;
	}

	vec2 Texture::GetSize() {
		float w, h;
		SDL_GetTextureSize(_texture, &w, &h);
		return vec2{ w, h };
	}

}

