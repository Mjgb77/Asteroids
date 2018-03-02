#include "Font.hpp"

Font::Font(std::string filePath, int size)
{
	m_font = TTF_OpenFont("../../fonts/font.ttf", size);
	if (!m_font) m_font = TTF_OpenFont("../../fonts/font.ttf", size);
}

