#pragma once
#include "Resource/Resource.h"
#include <string>

struct _TTF_Font;
struct SDL_Surface;

namespace anthemum
{
	struct Color;

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string filename, ...);
		void Load(const std::string& filename, int fontSize);

		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}