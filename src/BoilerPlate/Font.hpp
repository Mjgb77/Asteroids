#ifndef FONT_HPP_
#define FONT_HPP_

#include <SDL_ttf.h>

#include <string>

struct Font
{
public:
	/*CONSTRUCTOR*/
	Font(char * filePath, int size);

	TTF_Font* m_font;
private:
};

#endif /* FONT_HPP_ */
