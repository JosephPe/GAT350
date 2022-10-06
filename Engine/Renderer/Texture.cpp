#include "Texture.h"
#include "Renderer.h"
#include <SDL.h>
#include "..\Core\Logger.h"
#include <SDL_image.h>

namespace anthemum
{

	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(std::string filename, ...)
	{
		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		//Renderer* renderer = static_cast<Renderer*>(data);
		//return Create(*renderer, filename);
		return Create(renderer, filename);
	}

	bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
	{
		if (m_texture) SDL_DestroyTexture(m_texture);

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);

		if (m_texture == nullptr)
		{
			LOG(SDL_GetError());
			return false;
		}

		return true;
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());

		if (surface == nullptr)
		{
			LOG(SDL_GetError());
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr)
		{
			g_logger.Log(SDL_GetError());
			SDL_FreeSurface(surface);

			return false;
		}

		SDL_FreeSurface(surface);


		return true;
	}

	Vector2 Texture::GetSize() const
	{

		SDL_Point point;
		if (SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y) != 0)
		{
			g_logger.Log(SDL_GetError());
		}

		return Vector2(point.x, point.y);
	}

}