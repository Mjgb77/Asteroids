#include "Font.hpp"

Font::Font(char * filePath, int size)
{
	m_font = TTF_OpenFont(filePath, size);
}

