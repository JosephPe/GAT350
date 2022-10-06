#include "Font.h"
//#include "../Core/File.h"
#include <SDL_ttf.h>
#include <Engine.h>

namespace anthemum
{
	Font::Font(const std::string& filename, int fontSize)
	{
		//Load(anthemum::GetFilePath() + "\\jhand.tff", 96);
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != NULL) 
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), 16);

		return true;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);//(filename.c_str(), fontSize);
	}
	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c;
		c.r = color.r;
		c.g = color.g;
		c.b = color.b;
		c.a = color.a;
		SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

		if (surface == nullptr)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}
}